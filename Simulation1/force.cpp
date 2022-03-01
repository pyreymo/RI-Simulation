#include "Param.h"
#include "Force.h"
#include "Particle.h"
#include "Box.h"
#include <iostream>

#ifdef TWO_DIMENSIONAL_SIMULATION
void Force::update_2d(vector<vec2> x, vector<vec2>& f, Box box)
{
	f.resize(N);
	for (int i = 0; i < N; i++) f[i] = vec2(0, 0);

	double r2, r2i, r6i, lj;
	array2 box_size(BOX_X, BOX_Y);                  // 盒子大小
	array2 cell_num = round(box_size / CUTOFF); // 每个轴上多少个 cell
	array2 cell_size = box_size / cell_num;         // 每个 cell 多大
	int N_CELLS = cell_num.prod();                  // 一共多少个 cell

	// 存储每一个粒子所在 cell 的编号
	ParticleCell.resize(N);
	for (int i = 0; i < N; i++)
	{
		array2 cell_coord_pos = floor(array2(x[i]) / cell_size);
		ParticleCell[i] = cell_coord_pos.x() + cell_coord_pos.y() * cell_num.x();
	}

	// 存储每一个 cell 编号的实际 cell 坐标
	CellCoord_2d.resize(N_CELLS);
	int cellCounter = 0;
	for (int yi = 0; yi < cell_num.y(); yi++)
	{
		for (int xi = 0; xi < cell_num.x(); xi++)
		{
			CellCoord_2d[cellCounter] = vec2(xi, yi);
			cellCounter++;
		}
	}

	// 初始化两个链表
	HeadList.resize(N_CELLS);
	LinkedList.resize(N);
	for (int i = 0; i < N_CELLS; i++) HeadList[i] = -1;
	for (int i = 0; i < N; i++) LinkedList[i] = -1;

	// 构建 Verlet 表
	for (int i = 0; i < N; i++)
	{
		int cellnumber = ParticleCell[i];      // 第i个粒子在哪个cell
		LinkedList[i] = HeadList[cellnumber];  // 链表第i个元素指向头表中这个cell的
		HeadList[cellnumber] = i;              // 头表的该粒子对应的cell指向i
	}

	// 用编号遍历每个 cell
	for (int cell = 0; cell < N_CELLS; cell++)
	{
		// 遍历 cell 坐标的 [x-1,x+1]*[y-1,y+1]
		for (int cx1 = CellCoord_2d[cell].x() - 1; cx1 < CellCoord_2d[cell].x() + 2; cx1++)
		{
			for (int cy1 = CellCoord_2d[cell].y() - 1; cy1 < CellCoord_2d[cell].y() + 2; cy1++)
			{
				// 利用 PBC 转换超出范围的 cell
				int cx11 = cx1, cy11 = cy1;
				if (cx1 < 0) cx11 = cell_num.x() - 1;
				else if (cx1 > (cell_num.x() - 1)) cx11 = 0;
				if (cy1 < 0) cy11 = cell_num.y() - 1;
				else if (cy1 > (cell_num.y() - 1)) cy11 = 0;

				// use algorithm to determine cell number of neighbor cells
				int neighborCell = cx11 + cy11 * cell_num.x();

				// define atom i as HeadList value of 'center cell'
				int i = HeadList[cell];

				// scan for atom i in center cell (cell)
				int counter = 0;
				while (i > -1) // while HeadList vector space is null
				{
					counter++;
					int j = HeadList[neighborCell];
					while (j > -1) // while LinkedList vector space is null
					{
						if (i < j) // avoid double counting of each pair
						{
							vec2 dx = x[i] - x[j];
							box.restrictForcePBC(dx);

							r2 = dx.squaredNorm();
							r2i = 1. / r2;
							r6i = r2i * r2i * r2i;
							lj = 48 * r2i * r6i * (r6i - 0.5);

							if (r2 < CUTOFF_2)
							{
								vec2 temp_force = lj * dx;
								f[i] += temp_force;
								f[j] -= temp_force;
							}
						}
						j = LinkedList[j];
					}
					i = LinkedList[i];
				}
			}
		}

	}
}
#else
void Force::update_3d(vector<vec3> x, vector<vec3>& f, Box box)
{
	f.resize(N);
	for (int i = 0; i < N; i++) f[i] = vec3(0, 0, 0);

	double r2, r6i, lj;
	array3 box_size(BOX_X, BOX_Y, BOX_Z);           // 盒子大小
	array3 cell_num = round(box_size / CUTOFF); // 每个轴上多少个 cell
	array3 cell_size = box_size / cell_num;         // 每个 cell 多大
	int N_CELLS = cell_num.prod();                  // 一共多少个 cell

	// 存储每一个粒子所在 cell 的编号
	ParticleCell.resize(N);
	for (int i = 0; i < N; i++)
	{
		array3 cell_coord_pos = floor(array3(x[i]) / cell_size);
		ParticleCell[i] = cell_coord_pos.x() + cell_coord_pos.y() * cell_num.x() + cell_coord_pos.z() * cell_num.y() * cell_num.x();
	}

	// 记录每个 cell 编号对应的 cell 坐标
	CellCoord_3d.resize(N_CELLS);
	int cellCounter = 0;
	for (int zi = 0; zi < cell_num.z(); zi++)
	{
		for (int yi = 0; yi < cell_num.y(); yi++)
		{
			for (int xi = 0; xi < cell_num.x(); xi++)
			{
				CellCoord_3d[cellCounter] = vec3(xi, yi, zi);
				cellCounter++;
			}
		}
	}

	// 初始化两个链表
	HeadList.resize(N_CELLS);
	LinkedList.resize(N);
	for (int i = 0; i < N_CELLS; i++) HeadList[i] = -1;
	for (int i = 0; i < N; i++) LinkedList[i] = -1;

	// 构建 Verlet 表
	for (int i = 0; i < N; i++)
	{
		int cellnumber = ParticleCell[i];
		LinkedList[i] = HeadList[cellnumber];
		HeadList[cellnumber] = i;
	}

	for (int cell = 0; cell < N_CELLS; cell++)
	{
		for (int cx1 = CellCoord_3d[cell].x() - 1; cx1 < CellCoord_3d[cell].x() + 2; cx1++)
		{
			for (int cy1 = CellCoord_3d[cell].y() - 1; cy1 < CellCoord_3d[cell].y() + 2; cy1++)
			{
				for (int cz1 = CellCoord_3d[cell].z() - 1; cz1 < CellCoord_3d[cell].z() + 2; cz1++)
				{
					// 应用周期性边界条件
					int cx11 = cx1, cy11 = cy1, cz11 = cz1;
					if (cx1 < 0) cx11 = cell_num.x() - 1;
					else if (cx1 > (cell_num.x() - 1)) cx11 = 0;
					if (cy1 < 0) cy11 = cell_num.y() - 1;
					else if (cy1 > (cell_num.y() - 1)) cy11 = 0;
					if (cz1 < 0) cz11 = cell_num.z() - 1;
					else if (cz1 > (cell_num.z() - 1)) cz11 = 0;

					// use algorithm to determine cell number of neighbor cells
					int neighborCell = cx11 + cy11 * cell_num.x() + cz11 * cell_num.y() * cell_num.x();

					// define atom i as HeadList value of 'center cell'
					int i = HeadList[cell];

					// scan for atom i in center cell (cell)
					int counter = 0;
					while (i > -1) // while HeadList vector space is null
					{
						counter++;
						int j = HeadList[neighborCell];
						while (j > -1) // while LinkedList vector space is null
						{
							if (i < j) // avoid double counting of each pair
							{
								vec3 dx = x[i] - x[j];
								box.restrictForcePBC(dx);

								r2 = dx.squaredNorm();
								r6i = pow(r2, -3);
								lj = (48. / r2) * (r6i - 0.5) * r6i;	// E'(r) = F(/vec r)/vec r

								if (r2 < CUTOFF_2)
								{
									vec3 temp_force = lj * dx;
									f[i] += temp_force;
									f[j] -= temp_force;
								}
							}
							j = LinkedList[j];
						}
						i = LinkedList[i];
					}
				}
			}
		}

	}
}
#endif
