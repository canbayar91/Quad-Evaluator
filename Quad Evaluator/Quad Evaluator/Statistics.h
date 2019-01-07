#ifndef STATISTICS
#define STATISTICS

#include <string>
#include <vector>

class Statistics {
public:

	// Output the statistics to the given file
	virtual void outputStatistics(const std::string filename) = 0;

	// Create and output a histogram of the metric values
	virtual void createHistogram(const std::string filename) = 0;

protected:

	// Minimum metric value for the mesh
	double minimumValue;

	// Maximum metric value for the mesh
	double maximumValue;

	// List of the metric calculations for the mesh
	std::vector<double> values;

};

#endif
