#pragma once

/** Enumerations */

/** Used for notifying when Actors are created or removed. */
enum ActorEventType{  NewActor, RemovedActor};

/** Used for notifying when Components are created or removed. */
enum ComponentEventType{ NewMeshRenderer, NewCamera, NewLight, NewRigidBody, NewRigidStatic, NewEditorCollider, NewFontRenderer, RemovedRenderer, RemovedCamera, RemovedLight, RemovedRigidBody, RemovedRigidStatic ,RemovedFontRenderer};

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
enum RotateAxis { x, y, z };
enum MoveAxis { up, right, forward };
enum MoveMode { global, pivot };