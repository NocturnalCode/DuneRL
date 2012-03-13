/*
 *  Perlin.h
 *
 */

#include "Heightmap.h"

#ifndef PERLIN_H_INC
#define PERLIN_H_INC 

class Perlin : public Heightmap
{
private:
    int seed;
    
    double LinearInterpolate(double a, double b, double x);
    double CosineInterpolate(double a, double b, double x);
    double Noise(int x);
    double Noise(int x, int y);
    double Noise(int x, int y, int z);
    
    double SmoothNoise(int x);
    double SmoothNoise(int x, int y);
    double SmoothNoise(int x, int y, int z);
    double InterpolateNoise(double x);
    double InterpolateNoise(double x, double y);
    double InterpolateNoise(double x, double y, double z);
    double PerlinNoise(double x,int octaves, double persistance);
    double PerlinNoise(double x, double y,int octaves, double persistance);
    double PerlinNoise(double x, double y, double z,int octaves, double persistance);
    inline double abs(double arg);
    
public:
    Perlin(int size, int octaves, double persistance);
    double interpolatedAt(int size, unsigned i, unsigned j);
};

#endif /* PERLIN_H_INC */