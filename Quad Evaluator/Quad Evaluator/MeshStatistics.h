#ifndef MESH_STATISTICS
#define MESH_STATISTICS

#include "Statistics.h"

enum MetricType {
	SCALED_JACOBIAN,
	DISTORTION,
	WARPAGE,
	ASPECT_RATIO
};

class MeshStatistics : public Statistics {
public:

	// Constructor
	MeshStatistics(MetricType metricType);

	// Updates the statistics with the metric value of the new quad
	void updateStatistics(const double metric);

	// Outputs the statistics to the given file
	void outputStatistics(const std::string filename);

	// Creates and outputs a histogram of the metric values
	void createHistogram(const std::string filename);

	// Returns the minimum metric value
	const double getMinimumValue() const;

	// Returns the maximum metric value
	const double getMaximumValue() const;

	// Returns the average metric value
	const double getAverageValue() const;

private:

	// Evaluation function used in the statistics
	MetricType metricType;

	// Total of the metric values for all quadrilaterals in the mesh
	double totalValue;

	// Quadrilateral count of the mesh
	unsigned int quadrilateralCount;

	// Returns the string identifier of the metric type
	const std::string getMetricName() const;

};

#endif
