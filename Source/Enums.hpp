#pragma once

/** Enumerations */

/** Used for notifying when Actors are created or removed. */
enum ActorEventType{  NewActor,  RemovedActor};

/** Used for notifying when Components are created or removed. */
enum ComponentEventType{ NewMeshRenderer, NewCamera, NewLight, NewRigidBody, NewRigidStatic, NewEditorCollider, RemovedMeshRenderer, RemovedCamera, RemovedLight, RemovedRigidBody, RemovedRigidStatic};

/** Types supported for shader and materials*/
enum ShaderParamType {
	VEC4,
	FLOAT,
	TEXTURE
};


/** Is the application in editor or game mode?*/
enum EngineMode {editor, game};



/** Editor transform mode for currently selected actor*/
enum class TransformMode {move, rotate, scale, none};


/** Editor related enums */
enum class TransformAxis { x, y, z };
//enum TransformConstraintAxis { MoveLockX = 1,
//    MoveLockY = (1 << 2),
//    MoveLockZ = (1 << 3),
//    RotateLockX = (1 << 4),
//    RotateLockY = (1 << 5),
//    RotateLockZ = (1 << 6)};

struct TransformConstraintAxis
{
    enum Enum {
        MoveLockX = 1,
        MoveLockY = (1 << 2),
        MoveLockZ = (1 << 3),
        RotateLockX = (1 << 4),
        RotateLockY = (1 << 5),
        RotateLockZ = (1 << 6)
    };
};



enum RotateAxis { x, y, z };
enum MoveAxis { up, right, forward };
enum MoveMode { global, pivot };