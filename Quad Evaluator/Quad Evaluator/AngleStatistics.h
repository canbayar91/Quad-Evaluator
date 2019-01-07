#ifndef ANGLE_STATISTICS
#define ANGLE_STATISTICS

#include "Statistics.h"
#include "Quadrilateral.h"

class AngleStatistics : public Statistics {
public:

	// Constructor
	AngleStatistics(const std::vector<Quadrilateral> &mesh);

	// Output the statistics to the given file
	void outputStatistics(const std::string filename);

	// Create and output a histogram of the metric values
	void createHistogram(const std::string filename);

};

#endif
