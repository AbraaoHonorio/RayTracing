/*
 * objloader.h
 *
 *  Created on: Oct 31, 2014
 *      Author: Christian A. Pagot
 */

#ifndef UTILS_OBJLOADER_H_
#define UTILS_OBJLOADER_H_

#include "objparser.h"

void loadScene(char* filename, std::vector< TTriangle >& scene, TVector3& min, TVector3& max)
{
	int no_error = 1;
	obj_scene_data data;

	no_error = parse_obj_scene(&data, filename);

	if (no_error)
	{
		printf("File successfully opened...\n");

		TTriangle t;
		int vindex;

		for (int i=0; i<data.face_count; i++)
		{
			vindex = data.face_list[i]->vertex_index[0];
			t.v[0] = TVector3(	data.vertex_list[vindex]->e[0],
								data.vertex_list[vindex]->e[1],
								data.vertex_list[vindex]->e[2]);

			if (i == 1)
			{
				min.e[0] = t.v[0].e[0];
				min.e[1] = t.v[0].e[1];
				min.e[2] = t.v[0].e[2];

				max.e[0] = t.v[0].e[0];
				max.e[1] = t.v[0].e[1];
				max.e[2] = t.v[0].e[2];
			}
			else
			{
				min.e[0] = (min.e[0] < t.v[0].e[0])?min.e[0]:t.v[0].e[0];
				min.e[1] = (min.e[1] < t.v[0].e[1])?min.e[1]:t.v[0].e[1];
				min.e[2] = (min.e[2] < t.v[0].e[2])?min.e[2]:t.v[0].e[2];

				max.e[0] = (max.e[0] > t.v[0].e[0])?max.e[0]:t.v[0].e[0];
				max.e[1] = (max.e[1] > t.v[0].e[1])?max.e[1]:t.v[0].e[1];
				max.e[2] = (max.e[2] > t.v[0].e[2])?max.e[2]:t.v[0].e[2];
			}

			vindex = data.face_list[i]->vertex_index[1];
			t.v[1] = TVector3(	data.vertex_list[vindex]->e[0],
								data.vertex_list[vindex]->e[1],
								data.vertex_list[vindex]->e[2]);

			min.e[0] = (min.e[0] < t.v[1].e[0])?min.e[0]:t.v[1].e[0];
			min.e[1] = (min.e[1] < t.v[1].e[1])?min.e[1]:t.v[1].e[1];
			min.e[2] = (min.e[2] < t.v[1].e[2])?min.e[2]:t.v[1].e[2];

			max.e[0] = (max.e[0] > t.v[1].e[0])?max.e[0]:t.v[1].e[0];
			max.e[1] = (max.e[1] > t.v[1].e[1])?max.e[1]:t.v[1].e[1];
			max.e[2] = (max.e[2] > t.v[1].e[2])?max.e[2]:t.v[1].e[2];

			vindex = data.face_list[i]->vertex_index[2];
			t.v[2] = TVector3(	data.vertex_list[vindex]->e[0],
								data.vertex_list[vindex]->e[1],
								data.vertex_list[vindex]->e[2]);

			min.e[0] = (min.e[0] < t.v[2].e[0])?min.e[0]:t.v[2].e[0];
			min.e[1] = (min.e[1] < t.v[2].e[1])?min.e[1]:t.v[2].e[1];
			min.e[2] = (min.e[2] < t.v[2].e[2])?min.e[2]:t.v[2].e[2];

			max.e[0] = (max.e[0] > t.v[2].e[0])?max.e[0]:t.v[2].e[0];
			max.e[1] = (max.e[1] > t.v[2].e[1])?max.e[1]:t.v[2].e[1];
			max.e[2] = (max.e[2] > t.v[2].e[2])?max.e[2]:t.v[2].e[2];

			scene.push_back(t);
		}
	}
	else
		fprintf(stderr,"Something really BAD happened while trying to load the file...\n");
}

#endif /* UTILS_OBJLOADER_H_ */
