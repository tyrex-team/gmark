/*
 * cumulDistributionUtils.cpp
 *
 *  Created on: Sep 16, 2016
 *      Author: wilcovanleeuwen
 */

#include <iostream>
#include <cmath>
#include <utility>

#include "cumulativeDistributionUtils.h"

namespace std {

cumulativeDistributionUtils::cumulativeDistributionUtils() {
	// TODO Auto-generated constructor stub

}

cumulativeDistributionUtils::~cumulativeDistributionUtils() {
	// TODO Auto-generated destructor stub
}

int cumulativeDistributionUtils::calculateCDF(vector<graphNode*> & nodes, graphNode & sourceNode, double randomValue) {
	int sum = 0;
	vector<int> nonNormalizedResults;
	int i = 0;

	for(graphNode* & n: nodes) {
//		cout << "Node" << n->iterationId << " found with openConnections: " << n->getNumberOfOpenInterfaceConnections() << "\n";

		int possibleConnections = n->getNumberOfOpenInterfaceConnections();

		if (sourceNode.iterationId != -1) {
			possibleConnections = possibleConnections * (1 - sourceNode.getConnection(i));
		}

		nonNormalizedResults.push_back(possibleConnections);
		sum += possibleConnections;
		i++;
	}

	if(sum == 0) {
//		cout << "Sum of the pdf is 0\n";
		return -1;
	}

	float cumulValue = 0;
//	vector<float> normalizedCumulResults;
//	cout << "normalizedCumulResults size: " << nonNormalizedResults.size() << ": ";
	for(int i=0; i<nonNormalizedResults.size(); i++) {
		cumulValue += (float) nonNormalizedResults.at(i) / sum;
		if (randomValue <= cumulValue) {
			return nodes[i]->iterationId;
		}
//		normalizedCumulResults.push_back(cumulValue);
//		cout << to_string(temp) << ", ";
	}
//	cout << "\n";

//	return normalizedCumulResults;
	return nodes.size()-1;
}




vector<float> cumulativeDistributionUtils::zipfCdf(distribution zipfDistr, int iterationNumber) {
	float alpha = zipfDistr.arg2;
	int n = iterationNumber;
//	cout << "Zipfian n=" << n << endl;
//	cout << "Zipfian alpha=" << alpha << endl;

	vector<float> zipfian;
	float sum = 0.0;
	float step;
	for(int i=1; i<=n; i++) {
		step = pow(i, -1.0*alpha);
		zipfian.push_back(step);
		sum += step;
	}


	vector<float> cdf;
//	cout << endl << "CDF: " << endl;

	float tempSum = 0.0;
	for(int i=0; i<n; i++) {
		tempSum += zipfian.at(i) / sum;
//		cout << tempSum << ", ";
		cdf.push_back(tempSum);
	}
//	cout << endl;

	return cdf;
}



int cumulativeDistributionUtils::findPositionInCdf(vector<float> & cdf, double randomValue) {
	int i = 0;
//	cout << "Random value: " << randomValue << endl;
	for(float cumulProbValue: cdf) {
//		cout << "i=" << i << ", cumulProbValue=" << cumulProbValue << endl;
		if(randomValue <= cumulProbValue) {
			break;
		}
		i++;
	}
	if (i >= cdf.size() && i != 0) {
		 i= cdf.size()-1;
	}
//	cout << "Returning: " << i << endl;
	return i;
}


//vector<float> cumulativeDistributionUtils::calculateZipfCumulPercentagesForNnodes(vector<graphNode> & nodes, int currentEdgeTypeNumber, float alpha, int iterationNumber, bool findSource) {
////	cout << "Alpha=" << alpha << "\n";
//	vector<float> nonNormalizedNonCumul;
//	vector<pair<float, int>> posIdPairs;
//	float sum = 0;
//	int i = 0;
//	float step;
//	for(graphNode n: nodes) {
//		if (i > iterationNumber) {
////			cout << "Breaking loop, because of iteration\n";
//			break;
//		}
//
//		i++;
////		cout << "Node" << n.id << " found with pos: " << n.getPosition(currentEdgeTypeNumber, findSource) << "\n";
//		step = pow(i, -1.0*alpha);
//		sum += step;
//		nonNormalizedNonCumul.push_back(step);
//		posIdPairs.push_back(make_pair(n.getPosition(currentEdgeTypeNumber, findSource), i));
//	}
//
//	if(sum == 0) {
//		// TODO
//	}
//
////	printKeyValuesVector(posIdPairs);
//
//	// sort the posIdPairs on the key (which is the position of the node in the Zipfian distr)
//	// TODO: Find the order of this function (Big-O)
//	sort(posIdPairs.begin(), posIdPairs.end());
//
////	printKeyValuesVector(posIdPairs);
//
//	vector<posIdProbTripple> posIdPairsWithProbs;
//	int j=0;
//	for(pair<float, int> posIdPair: posIdPairs) {
//		posIdProbTripple tripple;
//		tripple.position = posIdPair.first;
//		tripple.id = posIdPair.second;
//		tripple.zipfProb = nonNormalizedNonCumul.at(j);
//
//		posIdPairsWithProbs.push_back(tripple);
//		j++;
//	}
//
//	// Sort posIdPairsWithProbs on the id's
//	sort(posIdPairsWithProbs.begin(), posIdPairsWithProbs.end());
//
////	printTripples(posIdPairsWithProbs);
//
////	return nonNormalizedNonCumul;
//
//	vector<float> normalizedCumulValues;
//	float tempSum = 0;
////	cout << "Sum=" << sum << "\n";
////	cout << "\nCumulArray: [";
//	for(int i=0; i<posIdPairsWithProbs.size(); i++) {
//		tempSum += posIdPairsWithProbs.at(i).zipfProb / sum;
////		cout << tempSum << "\n";
//		normalizedCumulValues.push_back(tempSum);
//	}
////	cout << "]\n\n";
//
//	return normalizedCumulValues;
//}
//
//
//
//void cumulativeDistributionUtils::printKeyValuesVector(vector<pair<float, int>> keyValues) {
//	cout << "KeyValues: [\n";
//	for(pair<float, float> p: keyValues) {
//		cout << "Pos=" << p.first << " id=" << p.second << "\n";
//	}
//	cout << "]\n";
//}
//
//void cumulativeDistributionUtils::printTripples(vector<posIdProbTripple> tripple) {
//	cout << "Tripples: [\n";
//		for(int i=0; i<tripple.size(); i++) {
//			cout << "Pos=" << tripple.at(i).position << " id=" << tripple.at(i).id << " Prob=" << tripple.at(i).zipfProb << "\n";
//		}
//		cout << "]\n";
//}

} /* namespace std */


