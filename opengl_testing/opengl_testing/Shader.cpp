#include "Shader.hpp"
#include <sstream>
#include "GraphicsSystem.hpp"

Shader::Shader()
{
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

Shader::Shader(string vertex_file_path, string fragment_file_path)
{
    
    vsFilename = vertex_file_path;
    fsFilename = fragment_file_path;
    
	LoadShaders();
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Shader::~Shader()
{
    glDeleteProgram(programID);
    
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Shader destroyed (" << nCount << " remaining)" << endl;
#endif
}


int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}



void Shader::LoadShaders(){

	// Create the shaders
    //GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    //GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLuint VertexShaderID = GraphicsSystem::getInstance()->createShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = GraphicsSystem::getInstance()->createShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vsFilename, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
		{
			VertexShaderCode += "\n" + Line;

			checkLine(Line);

		}
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fsFilename, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
		{
			FragmentShaderCode += "\n" + Line;

			checkLine(Line);

		}
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vsFilename.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();

    GraphicsSystem::getInstance()->compileShader(VertexShaderID,1,VertexSourcePointer);

//  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
//	glCompileShader(VertexShaderID);

	// Check Vertex Shader
//	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
//	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fsFilename.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();

    GraphicsSystem::getInstance()->compileShader(FragmentShaderID,1,FragmentSourcePointer);

//    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
//	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
//	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
//	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
//	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");

    GLuint ProgramID = GraphicsSystem::getInstance()->createShaderProgram();
    GraphicsSystem::getInstance()->attachAndLinkShader(ProgramID,VertexShaderID,FragmentShaderID);
    //GLuint ProgramID = glCreateProgram();
//	glAttachShader(ProgramID, VertexShaderID);
//	glAttachShader(ProgramID, FragmentShaderID);
//	glLinkProgram(ProgramID);

	// Check the program
//	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
//	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	std::vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
//	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

//GraphicsSystem::getInstance()->deleteShader(VertexShaderID);
//GraphicsSystem::getInstance()->deleteShader(FragmentShaderID);
//    glDeleteShader(VertexShaderID);
//	glDeleteShader(FragmentShaderID);

    programID = ProgramID;

    createUniformLocation();
}

void Shader::checkLine(const string& Line)
{
	size_t found = Line.find("uniform");
	if (found != string::npos)
	{
		vector<string> splitted = split(Line, ' ');

		if (splitted.size() >= 2)
		{
			if (splitted[1].compare("vec3"))
				params.insert(pair<string, ShaderParamType>(splitted[2], ShaderParamType::VEC3));
			else if (splitted[1].compare("float"))
				params.insert(pair<string, ShaderParamType>(splitted[2], ShaderParamType::FLOAT));

			cout <<"Shader param:"<< splitted[2] << endl;
		}
	}
}

void Shader::createUniformLocation()
{
	std::map<string, ShaderParamType>::iterator it = params.begin();

	for (; it != params.end(); it++)
	{
		const char* name = it->first.c_str();

        //paramID.insert(pair<string, GLuint>(it->first, glGetUniformLocation(programID, name)));

        GLint uniformLocation = GraphicsSystem::getInstance()->getUniformLocation(programID, name);
        paramID.insert(pair<string, GLuint>(it->first,uniformLocation) );
	}

}
