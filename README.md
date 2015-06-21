

  <body>

<p>GUInity is a 3D component-based game engine. It's a personal project started by myself, Guilherme Cunha.</p>

<p>My objectives with GUInity are:</p>

<UL>
<LI>Study and practice C++ in a large project. It's also a way of learning new C++11 concepts.
<LI>Get a better understanding of how game engines work under the hood.
<LI>Integrate several libraries into one software.
<LI>Develop with cross-platform in mind (currently GUInity works for both Windows and MacOS)
</UL>

<h3>
<a id="designer-templates" class="anchor" href="#designer-templates" aria-hidden="true"><span class="octicon octicon-link"></span></a>Name</h3>

<p>I chose the name GUInity because it summarizes well what I'm trying to do:</p>

<UL>
<LI>"GUI" stands for Gui-lherme not for Graphical User Interface. Because it's mine! My precious!
<LI>"nity" stands for Unity. It's the engine I have the most experience and the one that I'm using as a base for a lot of design decisions.
</UL>


<h3>
<a id="rather-drive-stick" class="anchor" href="#rather-drive-stick" aria-hidden="true"><span class="octicon octicon-link"></span></a>Dependencies</h3>

<p>Please note that even though I'm developing the engine from scratch, I'm also using a bunch of libraries to aid the development. For the purposes of this project, I've chosen to use, so far, the following libraries:</p>
<UL>
<LI>PhysX (3.1.1) Physics library developed by NVIDIA (https://developer.nvidia.com/physx-sdk)
<LI>FreeType (2.4.0) Free font library (http://www.freetype.org)
<LI>Boost(1.57.0) I don't believe this set of libraries need any introduction (http://www.boost.org)
<LI>GLFW(3.0.4) Cross-Platform library for handling window and basic OpenGL configurations (http://www.glfw.org)
<LI>libPNG .png library (http://www.libpng.org/pub/png/libpng.html)
<LI>FBX SDK (2015.1) .fbx files library (http://usa.autodesk.com/adsk/servlet/pc/item?siteID=123112&id=10775847)
<LI>FMOD Studio (1.05.02) Sound library (http://www.fmod.org/download)
</UL>
<p>Also, please note that due to possible licensing issues of the libraries, I'm not providing any of them in this repository. The benefit is that the repository is fairly compact. Also it would be very hard to provide the libraries to every operational system.
</p>

<h3>
<a id="authors-and-contributors" class="anchor" href="#authors-and-contributors" aria-hidden="true"><span class="octicon octicon-link"></span></a>Goal</h3>


<UL>
<LI>Get to a point where it's easy to create a simple game using code, in an component-based engine that has built-in physics, graphics and audio systems.
<LI>Have an editor to ease the development.
</UL>

<p>My goal is NOT to create a new and better Unity, but to understand how they were able to develop it. Unity has grown a lot over the last few years, they've been obviously doing something right. Therefore, I think it's a good foundation for a game engine.</p>

<h3>
<a id="overall_look" class="anchor" href="#overall_look" aria-hidden="true"><span class="overall_look"></span></a>Overall Look and Description</h3>

<p>So I've been talking about component-based here and there but what does that mean? Developers that are familiar with Unity are already used to this concept but if that's not the case, here's the main idea.</p>

<p>The game objects, Actors, are merely containers that exist in the World. All the behaviour that an Actor must have is done by adding and removing Components to it, not through standard inheritance. For example, to create an Actor that would be rendered on the screen, it would need a MeshFilter, reference to a Mesh Assets and a Mesh Renderer components. The code would be: </p>

<pre class="prettyprint">
<code>
// Create an Actor
shared_ptr<Actor> spaceShipRoot = Factory::CreateActor("SpaceShip");
// Set the scale of the Actor
spaceShipRoot->transform->setScale(glm::vec3(1.2,1.2,1.2));

// Add a MeshFilter to the Actor        
shared_ptr<MeshFilter> meshFilter = spaceShipRoot->AddComponent<MeshFilter>();
// Set the MeshFilter Mesh  
meshFilter->setMesh(spaceShipMesh);
// Add a MeshRenderer to the Actor        
shared_ptr<MeshRenderer> meshRenderer = spaceShipRoot->AddComponent<MeshRenderer>();
// Set the Material for the MeshRenderer
meshRenderer->setMaterial(spaceShipMaterial);
</code>
</pre>

<p> The components that are available right now are:</p>
<UL>
<LI> Camera - Adds to the Actor a Viewing Frustrum that's used to render the scene. Only one camera is supported at the moment.
<LI> Collider - Add Collision capabilities to the Actors. They can be used either for real physics simulation or as collision volumes (triggers). Colliders come in several shapes: Spheres, Boxes, Capsules and Meshes (convex hull of a mesh).
<LI> Light - Lights up the world. Currently there's only one type of Light, point light and only one is used by the rendering module.
<LI> MeshComponent - Has a reference to a Mesh. There are two types currently, a MeshFilter that references a MeshAsset and a FontMesh that generates a mesh based on a string.
<LI> MeshRenderer - Has a reference to a Material which describes how a mesh should be rendered on the screen.
<LI> RigidBody - Transforms a regular actor into a rigid body, allowing for physics simulation.
<LI> RigidStatic - The same as RigidBody but the body is always static.
<LI> ScriptComponent - Allows for custom behaviour
</UL>


<p> This piece of code above is enough for creating an Actor and rendering it on the screen but you must've noticed that it references some variables that were not declared in it. The variables that are missing are references to Assets. Assets are game assets that are imported or generated by GUInity. 

<p> The files that are inside the "data" folder are imported at the start of the program and can be accessed through the AssetsDatabase. Examples of Assets that are imported automatically are:</p></p>

<UL>
<LI> Textures (.png)
<LI> Meshes (.obj, .fbx)
<LI> Sound (.mp3, .wav, .ogg)
</UL>

<p>Examples of Assets that needs to be created manually are :</p>

<UL>
<LI> Shaders - Code that describes how to render a mesh (Vertex and Fragment shader)
<LI> Material - References a shader allowing for custom parameters
<LI> Fonts - A .ttf is imported and a Texture is generated based on an alphabet.
<LI> PhysicsMaterial - Describes the physical properties of an Actor that is under physics simulation
</UL>
 


<p> The piece of code that completes the previous one would be this: </p>
<pre class="prettyprint">
<code>
// Gets a reference to the Mesh spaceShip.fbx
shared_ptr&lt;Mesh&gt; spaceShipMesh =  AssetDatabase::getAsset&lt;Mesh&gt;(&quot;spaceShip.fbx&quot;);

// Gets a reference to the Texture spaceShipTexture.png
shared_ptr&lt;Texture&gt; spaceShipTexture = AssetDatabase::getAsset&lt;Texture&gt;(&quot;spaceShipTexture.png&quot;);

// Creates a Shader using a vertex shader and a fragment shader
shared_ptr&lt;Shader&gt; diffuseShader = AssetDatabase::createShader(&quot;LightShader&quot;, CommonData(&quot;vsLight.vs&quot;), 
							CommonData(&quot;fsLight.fragmentshader&quot;));
    
// Creates a Material using the LightShader created above
shared_ptr&lt;Material&gt; spaceShipMaterial = AssetDatabase::createMaterial(&quot;SpaceShipMaterial&quot;, diffuseShader);
// Sets the texture of the material
spaceShipMaterial-&gt;setParamTexture(&quot;_textureSampler&quot;, spaceShipTexture);
</code>
</pre>


<p>This is all very good but... how do I add custom behaviour to my Actors? I'm glad you asked! </p>
<p>Custom behaviour is added to the Actors in the form of ScriptComponents. They have certain functions that are called when the game is awakening, ticking or being shutdown. </p>

<p>One example of a custom behaviour is the following class PlayerScript</p>

<pre class="prettyprint">
<code>
// PlayerScript.h
class PlayerScript : public ScriptComponent
{
public:

  // The velocity drag
  float dragFactor;
  // How fast I move?
  float moveSpeed;
  // How fast I turn?
  float rotateSpeed;
  // Current velocity
  glm::vec3 velocity;

  // Called to initialize the script
  virtual void awake() override;
  // Called every frame
  virtual void tick(float deltaSecods) override;
  // Apply drag to velocity
  void applyDrag(float deltaSeconds);
  // Called when this Actor collided with another Actor  
  virtual void onCollision(shared_ptr&lt;Actor&gt; actor) override;

};
</code>
</pre>


<pre class="prettyprint">
<code>
// PlayerScript.cpp
void PlayerScript::awake()
{
  // Initialize variables
  dragFactor = 0.01f;
  moveSpeed = 0.1f;
  rotateSpeed = 5; 
}

void PlayerScript::tick(float deltaSeconds)
{
  // Get reference to actor that owns this script
  shared_ptr&lt;Actor&gt; lock = actor.lock();
  
  if (!lock)
    return;
    
  // Get reference to its transform  
  shared_ptr&lt;Transform&gt; transform = lock-&gt;transform;
    
  // If keyboard arrow up is being pressed  
  if (Input::getKey(GLFW_KEY_UP))
  {
    // Add to current velocity  
    velocity += transform-&gt;getUp() * moveSpeed; 
  }
  
  // If keyboard arrow up is being pressed  
  if (Input::getKey(GLFW_KEY_LEFT))
  {
    // Get current rotation and apply some rotation CW
    glm::quat rot = transform-&gt;getRotation();
    glm::quat left = glm::angleAxis(deltaSeconds * rotateSpeed, transform-&gt;getForward());
        
    transform-&gt;setRotation(left * rot);
  }
  if (Input::getKey(GLFW_KEY_RIGHT))
  {
    // Get current rotation and apply some rotation CCW
    glm::quat rot = transform-&gt;getRotation();
    glm::quat right = glm::angleAxis(deltaSeconds * rotateSpeed, -transform-&gt;getForward());
        
    transform-&gt;setRotation(right * rot);
  }
   
  // Translate the actor based on current velocity
  glm::vec3 position = transform-&gt;getPosition();

  position += velocity * deltaSeconds;

  transform-&gt;setPosition(position);
  
  // Apply drag to velocity
  applyDrag(deltaSeconds);
}

void PlayerScript::applyDrag(float deltaSeconds)
{
  // Add opposite force
  velocity -= velocity * dragFactor;
}

void PlayerScript::onCollision(shared_ptr&lt;Actor&gt; actor)
{
  // This actor collided with another one. Do something!    
}
</code>
</pre>

<p>This is just a basic introduction and there's much more to explore in GUInity.</p>

<h3>
<a id="support-or-contact" class="anchor" href="#support-or-contact" aria-hidden="true"><span class="octicon octicon-link"></span></a>Considerations</h3>

<p>Creating a game engine is not a simple task. Instead of trying to create the most optimized engine ever, I'm just "doing it", for now. Every now and then, when I feel like I completely grasped a concept, I go back and do my best to optimize it. Most of the times, I aim for readability and try to experiment with new features of C++11. I've been learning a lot from this project and intend to carry it on as well as I can.</p>
<p>I develop this project alongside my Master in Digital Media. This means I don't have as much time as I'd like to work on it. It also means that some periods this repository will have more updates than others.</p>

  </body>
</html>

