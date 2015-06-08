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
enum class TransformConstrainAxis { MoveLockX = 0,
    MoveLockY = (1 << 1),
    MoveLockZ = (1 << 2),
    RotateLockX = (1 << 3),
    RotateLockY = (1 << 4),
    RotateLockZ = (1 << 5)};

TransformConstrainAxis operator|(TransformConstrainAxis lhs, TransformConstrainAxis rhs) {
    return (TransformConstrainAxis) ((int)lhs| (int)rhs);
}

enum RotateAxis { x, y, z };
enum MoveAxis { up, right, forward };
enum MoveMode { global, pivot };