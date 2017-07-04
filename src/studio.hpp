#pragma once

#define MAKEID(d, c, b, a)	(((int)(a) << 24) | ((int)(b) << 16) | ((int)(c) << 8) | ((int)(d)))
#define IDSTUDIOHEADER		MAKEID('I', 'D', 'S', 'T') // little-endian "IDST"

typedef float vec3_t[3];

typedef struct
{
	int					id;
	int					version;

	char				name[64];
	int					length;

	vec3_t				eyeposition;			// ideal eye position
	vec3_t				min;					// ideal movement hull size
	vec3_t				max;

	vec3_t				bbmin;					// clipping bounding box
	vec3_t				bbmax;

	int					flags;

	int					numbones;				// bones
	int					boneindex;

	int					numbonecontrollers;		// bone controllers
	int					bonecontrollerindex;

	int					numhitboxes;			// complex bounding boxes
	int					hitboxindex;

	int					numseq;					// animation sequences
	int					seqindex;

	int					numseqgroups;			// demand loaded sequences
	int					seqgroupindex;

	int					numtextures;			// raw textures
	int					textureindex;
	int					texturedataindex;

	int					numskinref;				// replaceable textures
	int					numskinfamilies;
	int					skinindex;

	int					numbodyparts;
	int					bodypartindex;

	int					numattachments;			// queryable attachable points
	int					attachmentindex;

	int					soundtable;
	int					soundindex;
	int					soundgroups;
	int					soundgroupindex;

	int					numtransitions;		// animation node to animation node transition graph
	int					transitionindex;
} studiohdr_t;

// bones
typedef struct
{
	char				name[32];	// bone name for symbolic links
	int		 			parent;		// parent bone
	int					flags;		// ??
	int					bonecontroller[6];	// bone controller index, -1 == none
	float				value[6];	// default DoF values
	float				scale[6];   // scale for delta DoF values
} mstudiobone_t;


// bone controllers
typedef struct
{
	int					bone;	// -1 == 0
	int					type;	// X, Y, Z, XR, YR, ZR, M
	float				start;
	float				end;
	int					rest;	// byte index value at rest
	int					index;	// 0-3 user set controller, 4 mouth
} mstudiobonecontroller_t;



