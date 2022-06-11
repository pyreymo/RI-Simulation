#include "Force.h"

void Force::update_2d(vector<vec2> x, vector<vec2>& f, Box& box)
{
    f.resize(N);
    for (int i = 0; i < N; i++)
        f[i] = vec2(0, 0);

    double r2, r2i, r6i, lj;
    array2 box_size = array2(BOX_X, BOX_Y);
    array2 cell_num = round(box_size / CUTOFF);
    array2 cell_size = box_size / cell_num;
    int N_CELLS = cell_num.prod();

    ParticleCell.resize(N);
    for (int i = 0; i < N; i++) {
        array2 cell_coord_pos = floor(array2(x[i]) / cell_size);
        ParticleCell[i] = cell_coord_pos.x() + cell_coord_pos.y() * cell_num.x();
    }

    CellCoord_2d.resize(N_CELLS);
    int cellCounter = 0;
    for (int yi = 0; yi < cell_num.y(); yi++) {
        for (int xi = 0; xi < cell_num.x(); xi++) {
            CellCoord_2d[cellCounter] = vec2(xi, yi);
            cellCounter++;
        }
    }

    HeadList.resize(N_CELLS);
    LinkedList.resize(N);
    for (int i = 0; i < N_CELLS; i++)
        HeadList[i] = -1;
    for (int i = 0; i < N; i++)
        LinkedList[i] = -1;

    for (int i = 0; i < N; i++) {
        int cellnumber = ParticleCell[i];
        LinkedList[i] = HeadList[cellnumber];
        HeadList[cellnumber] = i;
    }

    for (int cell = 0; cell < N_CELLS; cell++) {
        for (int cx1 = CellCoord_2d[cell].x() - 1; cx1 < CellCoord_2d[cell].x() + 2; cx1++) {
            for (int cy1 = CellCoord_2d[cell].y() - 1; cy1 < CellCoord_2d[cell].y() + 2; cy1++) {
                int cx11 = cx1, cy11 = cy1;
                if (cx1 < 0)
                    cx11 = cell_num.x() - 1;
                else if (cx1 > (cell_num.x() - 1))
                    cx11 = 0;
                if (cy1 < 0)
                    cy11 = cell_num.y() - 1;
                else if (cy1 > (cell_num.y() - 1))
                    cy11 = 0;

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
                            box.restrictForce(dx);

                            r2 = dx.squaredNorm();
                            r2i = 1. / r2;
                            r6i = r2i * r2i * r2i;
                            lj = 48 * r2i * r6i * (r6i - 0.5);

                            if (r2 < CUTOFF_2) {
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