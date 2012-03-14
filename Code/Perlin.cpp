/*
 *  Perlin.cpp
 *
 */

#include "Perlin.h"
#include "Heightmap.h"
#include <math.h>

double Perlin::LinearInterpolate(double a, double b, double x)
{
	return  a*(1-x) + b*x;
}

double Perlin::CosineInterpolate(double a, double b, double x)
{
	double ft = x * (double)M_PI;
	double f = (1 - (double)cos(ft)) * 0.5f;

	return a * (1 - f) + b * f;
}

double Perlin::Noise(int x)
{
	x = (x << 13) ^ x;
	return (double)(1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double Perlin::Noise(int x, int y)
{
	int n = x + y * seed;
	n = (n<<13) ^ n;
	return (double)(1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);    
}

double Perlin::Noise(int x, int y, int z)
{

	int L = (x + y * seed);
	int M = (y + z * seed);
	unsigned N = (unsigned)(L + M * seed);
	N = (N << 13) ^ N;
	double d = (double)((N * (N * N * 15731 + 789221) + 1376312589) & 0x7fffffff);
	return (1.0f - (double)(d / 1073741824.0));
}

double Perlin::SmoothNoise(int x)
{
	return (Noise(x) / 2.0f) + (Noise(x - 1) / 4.0f) + (Noise(x + 1) / 4.0f);
}

double Perlin::SmoothNoise(int x, int y)
{
	double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16.0f;
	double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8.0f;
	double center = Noise(x, y) / 4.0f;
	return (corners + sides + center);
}

double Perlin::SmoothNoise(int x, int y, int z)
{
	double corners, sides, center;
	double averageZM1, averageZ, averageZP1;

	// average of neighbours in z-1
	corners = (Noise(x - 1, y - 1, z - 1) + Noise(x + 1, y - 1, z - 1) + Noise(x - 1, y + 1, z - 1) + Noise(x + 1, y + 1, z - 1)) / 16.0f;
	sides = (Noise(x - 1, y, z - 1) + Noise(x + 1, y, z - 1) + Noise(x, y - 1, z - 1) + Noise(x, y + 1, z - 1)) / 8.0f;
	center = Noise(x, y, z - 1) / 4.0f;
	averageZM1 = corners + sides + center;

	// average of neighbours in z
	corners = (Noise(x - 1, y - 1, z) + Noise(x + 1, y - 1, z) + Noise(x - 1, y + 1, z) + Noise(x + 1, y + 1, z)) / 16.0f;
	sides = (Noise(x - 1, y, z) + Noise(x + 1, y, z) + Noise(x, y - 1, z) + Noise(x, y + 1, z)) / 8.0f;
	center = Noise(x, y, z) / 4.0f;
	averageZ = corners + sides + center;

	// average of neighbours in z+1
	corners = (Noise(x - 1, y - 1, z + 1) + Noise(x + 1, y - 1, z + 1) + Noise(x - 1, y + 1, z + 1) + Noise(x + 1, y + 1, z + 1)) / 16.0f;
	sides = (Noise(x - 1, y, z + 1) + Noise(x + 1, y, z + 1) + Noise(x, y - 1, z + 1) + Noise(x, y + 1, z + 1)) / 8.0f;
	center = Noise(x, y, z + 1) / 4.0f;
	averageZP1 = corners + sides + center;

	return ((averageZM1 / 4.0f) + (averageZ / 2.0f) + (averageZP1 / 4.0f));
}

double Perlin::InterpolateNoise(double x)
{

	int X = (int)x;
	double fractional = x - X;

	double v1 = SmoothNoise(X);
	double v2 = SmoothNoise(X + 1);

	return CosineInterpolate(v1, v2, fractional);
}

double Perlin::InterpolateNoise(double x, double y)
{
	int X = (int)x;
	double fractionalX = x - X;

	int Y = (int)y;
	double fractionalY = y - Y;

	double v1 = SmoothNoise(X, Y);
	double v2 = SmoothNoise(X + 1, Y);
	double v3 = SmoothNoise(X, Y + 1);
	double v4 = SmoothNoise(X + 1, Y + 1);

	double i1 = CosineInterpolate(v1, v2, fractionalX);
	double i2 = CosineInterpolate(v3, v4, fractionalX);

	return CosineInterpolate(i1, i2, fractionalY);
}

double Perlin::InterpolateNoise(double x, double y, double z)
{
	int integerX = (int)x;
	double fracX = x - (double)integerX;

	int integerY = (int)y;
	double fracY = y - (double)integerY;

	int integerZ = (int)z;
	double fracZ = z - (double)integerZ;

	double v1 = SmoothNoise(integerX, integerY, integerZ);
	double v2 = SmoothNoise(integerX + 1, integerY, integerZ);
	double v3 = SmoothNoise(integerX, integerY + 1, integerZ);
	double v4 = SmoothNoise(integerX + 1, integerY + 1, integerZ);
	double v5 = SmoothNoise(integerX, integerY, integerZ + 1);
	double v6 = SmoothNoise(integerX + 1, integerY, integerZ + 1);
	double v7 = SmoothNoise(integerX, integerY + 1, integerZ + 1);
	double v8 = SmoothNoise(integerX + 1, integerY + 1, integerZ + 1);

	double i1 = CosineInterpolate(v1, v2, fracX);
	double i2 = CosineInterpolate(v3, v4, fracX);
	double i3 = CosineInterpolate(v5, v6, fracX);
	double i4 = CosineInterpolate(v7, v8, fracX);

	double i5 = CosineInterpolate(i1, i2, fracY);
	double i6 = CosineInterpolate(i3, i4, fracY);

	return CosineInterpolate(i5, i6, fracZ);
}

double Perlin::PerlinNoise(double x,int octaves, double persistance)
{
	double total = 0;

	for (int i = 0; i < octaves; i++)
	{
		double frequency = (double)pow(2, i);
		double amplitude = (double)pow(persistance, i);

		total += InterpolateNoise(x * frequency) * amplitude;
	}
	return total;
}

double Perlin::PerlinNoise(double x, double y,int octaves, double persistance)
{
	double total = 0;

	for (int i = 0; i < octaves; i++)
	{
		double frequency = (double)pow(2, i);
		double amplitude = (double)pow(persistance, i);

		total += InterpolateNoise(x * frequency, y * frequency) * amplitude;
	}
	return total;
}

double Perlin::PerlinNoise(double x, double y, double z,int octaves, double persistance)
{
	double total = 0;

	for (int i = 0; i < octaves; i++)
	{
		double frequency = (double)pow(2, i);
		double amplitude = (double)pow(persistance, i);

		total += InterpolateNoise(x * frequency, y * frequency, x * frequency) * amplitude;
	}
	return total;
}

inline double Perlin::abs(double arg)
{
    if (arg < 0) {
        return -arg;
    }
    return arg;
}

double Perlin::interpolatedAt(int size, unsigned i, unsigned j)
{
    //i and j are in size coordinate space land
    double X = (double)i*(double)Size/(double)size;
    double Y = (double)j*(double)Size/(double)size;
    
    int i_X = (int)X;
    X = X-i_X;
    int j_Y = (int)Y;
    Y = Y-j_Y;
    
//    if (i_X == Size-1) {
//        i_X = 0;
//    }
//    
//    if (j_Y == Size - 1) {
//        j_Y = 0;
//    }
    
    int j_Y_wrapped = j_Y+1;
    if (j_Y_wrapped == Size) {
        j_Y_wrapped = 0;
    }
    int i_X_wrapped = i_X+1;
    if (i_X_wrapped == Size) {
        i_X_wrapped = 0;
    }
    
    
    
    double v1 = j_Y == 0 ? 0:(SmoothNoise(i_X, j_Y));
	double v2 = j_Y == 0 ? 0:(SmoothNoise(i_X_wrapped, j_Y));
    
	double v3 = j_Y_wrapped == 0 ? 0 : (SmoothNoise(i_X, j_Y+1));
	double v4 = j_Y_wrapped == 0 ? 0 : (SmoothNoise(i_X_wrapped, j_Y+1));
    
    double i1 = CosineInterpolate(v1, v2, X);
	double i2 = CosineInterpolate(v3, v4, X);
    
	return CosineInterpolate(i1, i2, Y);
}

/// <summary>
/// Generates 2D perlin noise
/// </summary>
/// <param name="width">The width.</param>
/// <param name="height">The height.</param>
/// <param name="octaves">The octaves.</param>
/// <returns></returns>
Perlin::Perlin(int size, int octaves, double persistence) : Heightmap(size)
{
    seed = arc4random();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			put(i, j,PerlinNoise(i,j,octaves, persistence));

}
