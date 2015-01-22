#pragma once


enum class TransformAxis {x,y,z};


enum RotateAxis {x,y,z};

enum MoveAxis { up, right, forward };

enum MoveMode { global, pivot };

enum ActorEventType{  NewActor, RemovedActor};

enum ComponentEventType{ NewMeshRenderer, NewCamera, NewLight, NewRigidBody, NewRigidStatic, NewEditorCollider, RemovedRenderer, RemovedCamera, RemovedLight, RemovedRigidBody, RemovedRigidStatic };

enum EngineMode {editor, game};

enum class TransformMode {move, rotate, scale, none};
