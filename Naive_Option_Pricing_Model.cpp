/* This is the Preprocessing*/

// requires Random1.cpp  

#include <iostream> //links the library to our code   
#include <cmath> 
#include <Random_1.h>
using namespace std;


// Below we make the declaration for our function 
double SimpleMonteCarlo(double Expiry,
	double Strike,
	double Spot,
	double Volatility,
	double riskFreeRate,
	unsigned long NumberOfPaths)

	// Below is the implementation of our methodology 
{
	double variance = pow(Volatility, 2);
	double RootVariance = sqrt(variance);
	double itoCorrection = -0.5 * variance * Expiry;

	double movedSpot = Spot * exp(riskFreeRate * Expiry + itoCorrection);
	double thisSpot; // initialise the spot value for current time 
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianbyBoxMuller();
		thisSpot = movedSpot * exp(RootVariance* sqrt(Expiry) * thisGaussian);
		double thisPayoff = thisSpot - Strike;
		thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-riskFreeRate * Expiry);
	return mean;
}

int main()
{
	double Expiry;
	double Strike;
	double Spot;
	double Volatility;
	double riskFreeRate;
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter Strike\n";
	cin >> Strike;

	cout << "\nEnter Spot\n";
	cin >> Spot;

	cout << "\nEnter Volatility\n";
	cin >> Volatility;

	cout << "\nEnter Risk Free Rate\n";
	cin >> riskFreeRate;

	cout << "\nEnter number of paths\n";
	cin >> NumberOfPaths;

	double result = SimpleMonteCarlo(Expiry,
		Strike,
		Spot,
		Volatility,
		riskFreeRate,
		NumberOfPaths);

	cout << "\nThe price is " << result << "\n";

	double tmp;
	cin >> tmp;

	return 0;

}