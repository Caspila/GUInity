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
	TEXTURE,
    VEC2
};


/** Is the application in editor or game mode?*/
enum EngineMode {editor, game};



/** Editor transform mode for currently selected actor*/
enum class TransformMode {move, rotate, scale, none};


/** Editor related enums */
enum class TransformAxis { x, y, z };


struct TransformConstraintAxis
{
    enum Enum {
        X_MOVE_LOCK = 1,
        Y_MOVE_LOCK = (1 << 2),
        Z_MOVE_LOCK = (1 << 3),
        X_ROTATE_LOCK = (1 << 4),
        Y_ROTATE_LOCK = (1 << 5),
        Z_ROTATE_LOCK = (1 << 6)
    };
};

enum CurveAnimationType {X_MOVE, Y_MOVE, Z_MOVE, X_ROTATE, Y_ROTATE, Z_ROTATE, X_SCALE, Y_SCALE, Z_SCALE };

enum RotateAxis { x, y, z };
enum MoveAxis { up, right, forward };
enum MoveMode { global, pivot };