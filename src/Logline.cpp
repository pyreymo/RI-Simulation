 #include "Logline.h"

 void Logline::print_log_2d(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params)
 {
 	ofstream os;
 	os.open(LOG_ADDR, std::ios_base::app);
 	os << "Iter " << iter << endl;
 	for (size_t i = 0; i < N; i++)
 	{
 		os << i << "," << x[i].x() << "," << x[i].y() << endl;
 	}
 	for (auto m : params)
 	{
 		os << "@ \t" << m.first << "\t" << m.second << endl;
 	}
 	os.close();
 }

 void Logline::init_log_2d(string LOG_ADDR, vector<vec2> x, map<string, double> params)
 {
 	ofstream os;
 	os.open(LOG_ADDR, std::ios_base::out);

 	os << "# N\t" << N << endl;
 	os << "# Radius\t" << sqrt(3) / 2.0 * PLY * S << endl;
 	os << "# Length\t" << LEN * S << endl;

 	os << "# TimeStep\t" << TIME_STEP << endl;
 	os << "# IterNum\t" << ITER_NUM << endl;
 	os << "# LogStep\t" << LOG_STEP << endl;

 	os << "# Temp\t" << TEMP << endl;
 	os << "# Cutoff\t" << CUTOFF << endl;

 	os << "# BOX_X\t" << BOX_X << endl;
 	os << "# BOX_Y\t" << BOX_Y << endl;

 	os.close();

 	print_log_2d(LOG_ADDR, 1, x, params);
 }

 Logline::Logline(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance)
     : Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance)
 {
 }