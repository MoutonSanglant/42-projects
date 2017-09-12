#ifndef SCENE_H
# define SCENE_H

#include "transform.h"

typedef struct	s_scene
{
	const char	*path;
	t_transform	world;

}				t_scene;

t_scene		*new_scene(const char *path);


#endif
