#include "main.h"

int main(void)
{
	// image: is the object that will store and save the final image.
	TImage image(IMAGE_WIDTH, IMAGE_HEIGHT);

	// loadScene: loads the OBJ file that contains the geometric description of the scene.
	// This function returns two vectors: min and max. These two vectors store
	// the minimum and maximum vertices of the AABB that contains the loaded scene.

	//loadScene("boxes.obj", scene, min, max);
	loadScene("monkey.obj", scene, min, max);

    //sceneTemp = scene;

    TTriangle t;
    TVector3 Minimo, Maximo;
    int cont = 0;

    for(int k = 0; k < scene.size(); k++)
    {
        Maximo = Max_box(scene[k]);
        Minimo = Min_box(scene[k]);

        for(int X = Minimo.e[0]; X <= Maximo.e[0]; X++)
        {
            for(int Y = Minimo.e[1]; Y <= Maximo.e[1]; Y++)
            {
                for(int Z = Minimo.e[2]; Z <= Maximo.e[2]; Z++)
                {
                    int n = func_hash(X,Y,Z);
                    HashTable[n].push_back(&(scene[k]));
                    cont++;
                }

            }
        }
    }//*/

    std::cout << "Quantidade de triangulos na tabela: " << cont << std::endl;

	fprintf(stderr,"Image resolution: w %i, h %i\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	fprintf(stderr,"# of triangles: %i\n", scene.size());

	// camPosition: is computed from the scene's AABB.
	TVector3 camPosition((min.e[0] + max.e[0]) * 0.5f, (min.e[1] + max.e[1]) * 0.5f, max.e[2] + 3.0f);
	TVector3 camLookAt((min.e[0] + max.e[0]) * 0.5f, (min.e[1] + max.e[1]) * 0.5f, 0.0f);
	TVector3 camUp( 0.0f, 1.0f, 0.0f);

	// Creates the camera.
	TCamera camera(camPosition,
				   camLookAt,
				   camUp,
				   1.0f,			// aspect
				   1.0f,			// viewplane distance
				   IMAGE_WIDTH,		// image width
				   IMAGE_HEIGHT);	// image_height

	fprintf(stderr,"Rendering line # ");

	// The following nestes loops run over all pixels, with coordinates (x, y), on the screen.

	TVector3 in, out, minimo, maximo;

	for (int y=0; y<IMAGE_HEIGHT; y++)
	{
		for (int x=0; x<IMAGE_WIDTH; x++)
		{
			float d = 9999.9f;
			float tmp_d;

			// The camera generates a ray object for each pixel (x,y) on the screen.
			TRay ray = camera.getRay(x, y);

			// **********************************************************************************************************
			// Calculando bounding box do disparo

			alpha(ray, in, out);
			modela_ray(in,out, minimo, maximo);

			// **********************************************************************************************************

			// The loop below rus over each triangle of the scene.
            for(int Xt = minimo.e[0]; Xt <= maximo.e[0]; Xt++)
            {
                for(int Yt = minimo.e[1]; Yt <= maximo.e[1]; Yt++)
                {
                    for(int Zt = minimo.e[2]; Zt <= maximo.e[2]; Zt++)
                    {
                        int n = func_hash(Xt, Yt, Zt);

                        for(int cont = 0; cont < HashTable[n].size(); cont++)
                        {
                            t = *HashTable[n][cont];
                            // The current ray is tested for intersection against each triangle in the scene.
                            if (ray.hit(t, tmp_d))
                            {
                                // if the ray intersects a triangle, the distance between the camera and
                                // the intersection point is recorded in the d (distance) variable.
                                d = (tmp_d < d)?tmp_d:d;
                                image.writePixel(x, y, d);
                            }
                        }
                    }
                }
            }
		}
		fprintf(stderr," %i ", y);
	}

	fprintf(stderr,"... done!\n");

	// Save the final ray traced image.
	// The distance to the intersection point is normalized and used as the color
	// of the corresponding pixel on the final image.
	// In the end, one will get a gray scale image, where dark pixels represent intersection
	// points that are closer to the camera, whereas whiter points represent intersection
	// points that are more distant.
	image.save("image.ppm");

	return 0;
}
