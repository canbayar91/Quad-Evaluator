#include "MeshStatistics.h"
#include <iostream>
#include <fstream>
#include <cfloat>

MeshStatistics::MeshStatistics(MetricType metricType) {
	this->metricType = metricType;
	minimumValue = DBL_MAX;
	maximumValue = -DBL_MAX;
	totalValue = 0;
	quadrilateralCount = 0;
}

void MeshStatistics::updateStatistics(const double value) {

	// NaN check in order to ignore error cases
	if (!isnan(value)) {

		// Update the total metric value and the counter
		totalValue += value;
		quadrilateralCount++;

		// Insert the new value into the list
		values.push_back(value);

		// Update the minimum value, if the new value is smaller
		if (value < minimumValue) {
			minimumValue = value;
		}

		// Update the maximum value, if the new value is bigger
		if (value > maximumValue) {
			maximumValue = value;
		}
	}
}

void MeshStatistics::outputStatistics(const std::string filename) {

	// Open the output file
	std::ofstream file;
	file.open(filename, std::ios::app);

	// Output the statistics
	file << "Statistics for " << getMetricName() << " metric:" << std::endl;
	file << "Minimum value: " << getMinimumValue() << std::endl;
	file << "Maximum value: " << getMaximumValue() << std::endl;
	file << "Average value: " << getAverageValue() << std::endl << std::endl;

	// Close the file
	file.close();
}

void MeshStatistics::createHistogram(const std::string filename) {

	// Delete the file, if it is previously created
	std::remove(filename.c_str());
	
	// Open the output file
	std::ofstream file;
	file.open(filename, std::ios::app);

	// Iterate through the list and output the values
	for (size_t i = 0; i < values.size(); i++) {
		file << values[i] << std::endl;
	}

	// Close the file
	file.close();

}

const double MeshStatistics::getMinimumValue() const {
	return minimumValue;
}

const double MeshStatistics::getMaximumValue() const {
	return maximumValue;
}

const double MeshStatistics::getAverageValue() const {
	return totalValue / quadrilateralCount;
}

const std::string MeshStatistics::getMetricName() const {

	// Set the name depending on the metric type
	std::string metricName;
	switch (metricType) {
	case SCALED_JACOBIAN:
		metricName = "Scaled Jacobian";
		break;
	case DISTORTION:
		metricName = "Distortion";
		break;
	case WARPAGE:
		metricName = "Warpage";
		break;
	case ASPECT_RATIO:
		metricName = "Aspect Ratio";
		break;
	}

	// Return the name of the metric
	return metricName;
}
