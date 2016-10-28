/*
 * main.h
 *
 *  Created on: Dec 01, 2014
 *  Author: Abraão Állysson dos Santos Honório 
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "utils/misc.h"
#include "utils/camera.h"
#include "utils/ray.h"
#include "utils/image.h"
#include "utils/triangle.h"
#include "utils/objloader.h"

#define IMAGE_WIDTH		512
#define IMAGE_HEIGHT	512
#define FOCAL_LENGTH	1.0f
#define N 1571

TVector3 min, max;

std::vector<TTriangle> scene;
std::vector<TTriangle*> HashTable[N];
std::vector<TTriangle>::iterator iPtrT;

double A = 0.6180339887;

float scaleGrayLevels(float d, float d1, float d0)
{
	if (d >= d0)
		return 0.0f;

	if (d <= d1)
		return 1.0f;

	return (d - d1) / (d0 - d1);
}
int func_hash(int& X, int& Y, int& Z) //elabora a função de hash
{
    double val;
    val = fabs(19*X+5*Y+11*Z) * A;
    val = val - int(val);

    return floor(N * val); //N*(KA mod 1)
}

TVector3 Min_box(TTriangle &t)//Calcula a boundingbox minima dos vértices
{
    TVector3 Min;

    for(int i=0; i < 3; i++)
        Min.e[i] = ceil(t.v[0].e[i]);

    for(int j=0; j < 3; j++)
        for(int i=0; i < 3; i++)
            if(t.v[i].e[j] < Min.e[j])
                Min.e[j] = ceil(t.v[i].e[j]);

    return Min;
}

TVector3 Max_box(TTriangle &t)//Calcula a boundingbox minima dos vértices
{
    TVector3 Max;

    for(int i=0; i < 3; i++)
        Max.e[i] = ceil(t.v[0].e[i]);

    for(int j=0; j < 3; j++)
        for(int i=0; i < 3; i++)
            if(t.v[i].e[j] > Max.e[j])
                Max.e[j] = ceil(t.v[i].e[j]);

    return Max;
}

void alpha(TRay &ray, TVector3 &entrada, TVector3 &saida)//Calcula os pontos e bounding box do raio
{
    //alfa do ponto de entrada - poderia ter sido calculado direto no main
    double alpha_in;

    saida.e[2] = 99999;

    alpha_in = (max.e[2] - ray.ray[0].e[2]) / ray.ray[1].e[2];

    entrada.e[0] = ray.ray[0].e[0] + ray.ray[1].e[0] * alpha_in;
    entrada.e[1] = ray.ray[0].e[1] + ray.ray[1].e[1] * alpha_in;
    entrada.e[2] = max.e[2];

    //Vetor onde cada posição é -> [0]aRIGHT, [1]aLEFT, [2]aTOP, [3]aBOTTON, [4]aBACK
    double bounds[5], maior = 999999999.99;
    TVector3 temp_saida;

    bounds[0] = (max.e[0] - ray.ray[0].e[0]) / ray.ray[1].e[0];
    bounds[1] = (min.e[0] - ray.ray[0].e[0]) / ray.ray[1].e[0];
    bounds[2] = (max.e[1] - ray.ray[0].e[1]) / ray.ray[1].e[1];
    bounds[3] = (min.e[1] - ray.ray[0].e[1]) / ray.ray[1].e[1];
    bounds[4] = (min.e[2] - ray.ray[0].e[2]) / ray.ray[1].e[2];

    for(int i=1; i < 5; i++)
    {
        for(int j=0; j < 3; j++)
            if(bounds[i] >= alpha_in && bounds[i] <= maior)
            {
                temp_saida.e[j] = ray.ray[0].e[j] + ray.ray[1].e[j] * bounds[i];
                maior = bounds[i];
            }
    }
    saida = temp_saida;
}

void modela_ray(TVector3 &entrada, TVector3 &saida, TVector3 &minimo, TVector3 &maximo)//Verifica se o ponto minimo e máximo está no plano
{
    for(int i=0; i < 3; i++)
        if(entrada.e[i] < saida.e[i])
        {
            minimo.e[i] = ceil(entrada.e[i]);
            maximo.e[i] = ceil(saida.e[i]);
        }
        else
        {
            maximo.e[i] = ceil(entrada.e[i]);
            minimo.e[i] = ceil(saida.e[i]);
        }
}


#endif /* MAIN_H_ */
