
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#define GLM_FORCE_RADIAN
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fmt/format.h>
#include <imgui.h>
#include <memory>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "ImGuiFileDialog.h"
#include "WenCheng.h"

struct AllObject
{
	glm::vec3 color{ 1.0f };						  //color of obj
	
	int shape = 0;		
	
	//1. sphere
	//2. cube
	//3. cylinder
	//4. torus
	//5. cone
	
	
	bool have_texture = false;						  //check if user load texture
	std::string name = "";
	int text = -1;							 //location of obj and texture
							 
	float trans[3] = { 0.0f,0.0f,0.0f };				//translate of the object
	//glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);    //translate of the object
	float rot[3] = { 0.0f,0.0f,0.0f };				  //rotation of the object
	float scale[3] = { 1.0f,1.0f,1.0f };				  //scale of the object
};


static void error_callback(int error, const char* description)
{
    std::cerr<<fmt::format("Error: {0}\n", description);
}

int currentID = 0;
int object_number = 0;
int texture_number = 0;
int mesh_number = 0;
float fov = 45.0f;
bool firstMouse = true;
float lastX = 1000.0f / 2.0;
float lastY = 800.0f / 2.0;
float yaw = -0.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
AllObject all_object[50];
std::string AllText[50];
std::string AllMesh[50];
//bool show_demo_window = true;
//bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.0f, 0.5f, 0.5f, 1.00f);
StaticMesh S[50];
Texture2D T[50];
//Texture2D T[50];
glm::vec3 total;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 150.0f)
		fov -= (float)yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 150.0f)
		fov = 150.0f;
}

bool middle_hold = false;

void processInput(GLFWwindow *window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		middle_hold = true;
	}
	else
		middle_hold = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	if (middle_hold)
	{
		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;


		total.x = -pitch;
		total.y = yaw;
	}

	
}

int findText(std::string compare)
{
	
	for (int i = 0; i < texture_number; i++)
	{
		if (AllText[i] == compare)
			return i;
	}
	return -1;
}
int findMesh(std::string compare)
{
	
	for (int i = 0; i < mesh_number; i++)
	{
		if (AllMesh[i] == compare)
			return i;
	}
	return -1;
}

void Gui()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	static bool openobj = false;
	static bool opentext = false;

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		//ImGui::Begin("HI");
		ImGui::ColorEdit3("background color", (float*)&clear_color); // Edit 3 floats as a color
		//if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
		//	show_demo_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


		ImGui::PushItemWidth(80);
		//1. sphere 2. cube 3. cylinder 4. torus 5. cone
		const char* items[] = { "sphere", "cube", "cylinder", "torus", "cone" }; //01234
		static int item = -1;
		ImGui::Combo("", &item, items, IM_ARRAYSIZE(items)); ImGui::SameLine();
		if (ImGui::Button("ADD"))
		{
			
			if (item != -1)
			{
				object_number++;
				all_object[object_number - 1].shape = item +1;
				all_object[object_number - 1].name = AllMesh[item];
			}
				
			
		}
		ImGui::SameLine();
		ImGui::Text("or"); ImGui::SameLine();

		if (ImGui::Button("Load obj"))
		{
			openobj = true;
			
		}
		ImGui::PopItemWidth();


		static std::string filePathName = "";
		static std::string path = "";
		static std::string fileName = "";
		static std::string filter = "";

		if (openobj || opentext)
		{
			if (ImGuiFileDialog::Instance()->FileDialog("Choose File", ".obj\0.png", ".", ""))
			{
				if (opentext)
				{
					if (ImGuiFileDialog::Instance()->IsOk == true)
					{

						fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
						int temp = findText(fileName);

						if (temp == -1)
						{
							texture_number++;
							all_object[currentID - 1].text = texture_number;
							AllText[texture_number - 1] = ImGuiFileDialog::Instance()->GetCurrentFileName();
							T[texture_number - 1] = Texture2D::LoadFromFile(ImGuiFileDialog::Instance()->GetFilepathName());

						}
						else
						{
							all_object[currentID - 1].text = temp+1;
							
						}

						all_object[currentID - 1].have_texture = true;
						
						/*filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
						path = ImGuiFileDialog::Instance()->GetCurrentPath();
						fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
						filter = ImGuiFileDialog::Instance()->GetCurrentFilter();*/
					}
					else
					{
						
						all_object[currentID - 1].have_texture = false;
						/*filePathName = "";
						path = "";
						fileName = "";
						filter = "";*/
					}
					opentext = false;
				}
				else
				{
					if (ImGuiFileDialog::Instance()->IsOk == true)
					{
						object_number++;
						//all_object[object_number - 1].mesh = ImGuiFileDialog::Instance()->GetFilepathName();
						//all_object[currentID - 1].have_obj = true;
						fileName= ImGuiFileDialog::Instance()->GetCurrentFileName();
						int temp = findMesh(fileName) ;

						if (temp == -1)
						{
							mesh_number++;
							all_object[object_number - 1].name = ImGuiFileDialog::Instance()->GetCurrentFileName();
							AllMesh[mesh_number - 1] = all_object[object_number - 1].name;
							S[mesh_number - 1] = StaticMesh::LoadMesh(ImGuiFileDialog::Instance()->GetFilepathName());
							all_object[object_number - 1].shape = mesh_number ;
							
						}
						else
						{
							all_object[object_number - 1].shape = temp+1;
							all_object[object_number - 1].name = AllMesh[temp];
						}
							
						
						
					}

					openobj = false;
				}



			}
		}

		/*if (filePathName.size() > 0) ImGui::Text("Choosed File Path Name : %s", filePathName.c_str());
		if (path.size() > 0) ImGui::Text("Choosed Path Name : %s", path.c_str());
		if (fileName.size() > 0) ImGui::Text("Choosed File Name : %s", fileName.c_str());
		if (filter.size() > 0) ImGui::Text("Choosed Filter : %s", filter.c_str());*/
		
		ImGui::Separator();

		ImGui::Text("All objects: ");


		ImGui::Separator();


		for (int i = 0; i < object_number; i++)
		{
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ID: %d", i + 1);
			//ImGui::Text("ID: %d",i+1);
			ImGui::SameLine();
			//1. sphere 2. cube 3. cylinder 4. torus 5. cone

			ImGui::Text("Name: %s", all_object[i].name.c_str());
			
			ImGui::Text("color:"); ImGui::SameLine();
			ImGui::PushID(i);
			ImGui::ColorEdit3("", glm::value_ptr(all_object[i].color));
			ImGui::InputFloat3("Trans", all_object[i].trans);
			ImGui::InputFloat3("Rot", all_object[i].rot);
			ImGui::InputFloat3("Scale", all_object[i].scale);





			if (ImGui::Button("Load Texture"))
			{
				opentext = true;
				currentID = i + 1;
			}

			ImGui::PopID();
			ImGui::Separator();

		}





	}


	// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
	//if (show_demo_window)
	//{
	//	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
	//	ImGui::ShowDemoWindow(&show_demo_window);
	//}

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}


int main(void)
{
	
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	// Good bye Mac OS X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1000, 800, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL()) {
		exit(EXIT_FAILURE);
	}




	

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Setup style
	ImGui::StyleColorsDark();

	
	
    T[0] = Texture2D::LoadFromFile("../textures/sun.png");
	S[0]= StaticMesh::LoadMesh("../resource/sphere.obj");
	S[4] = StaticMesh::LoadMesh("../resource/cone.obj");
	S[1]  = StaticMesh::LoadMesh("../resource/cube.obj");
	S[2] = StaticMesh::LoadMesh("../resource/cylinder.obj");
	S[3] = StaticMesh::LoadMesh("../resource/torus.obj");
	auto prog = Program::LoadFromFile("../resource/vs.vert", "../resource/fs.frag");
	AllText[0] = "sun.png";
	AllMesh[0] = "sphere.obj"; AllMesh[1] = "cube.obj"; AllMesh[2] = "cylinder.obj";
	AllMesh[3] = "torus.obj"; AllMesh[4] = "cone.obj";
	mesh_number = 5; texture_number = 1;
	//1. sphere 2. cube 3. cylinder 4. torus 5. cone

	
    // Do not remove {}, why???
	{
		// text and mesh, shader => garbage collector
		//auto g1 = Protect(text_sun);
		//auto g4 = Protect(sphere);
		//auto g5 = Protect(prog);0
		//auto g6 = Protect(cone);
		//auto g7 = Protect(cube);
		//auto g8 = Protect(cylinder);
		//auto g9 = Protect(torus);
		

		/*if (!sphere.hasNormal() || !sphere.hasUV()) {
			std::cerr << "mesh_sun does not have normal or uv\n";
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}*/

		
		
		
		
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		
		//Main loop
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);

			glfwPollEvents();

			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);

			prog["vp"] = glm::perspective(fov / 180.0f*3.1415926f, 640.0f / 480.0f, 0.1f, 10000.0f)*
				glm::lookAt(glm::vec3{ 0, 0, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });

			
			int aaa = 1;
			

			//draw object
			
			for (int i = 0; i < object_number; i++)
			{

				prog["model"] = 
					glm::rotate(glm::mat4(1.0f), total.x * 3.1415926f / 180.0f, glm::vec3(1, 0, 0))
					*glm::rotate(glm::mat4(1.0f), total.y * 3.1415926f / 180.0f, glm::vec3(0, 1, 0))
					*glm::translate(glm::mat4(1.0f), glm::vec3(all_object[i].trans[0], all_object[i].trans[1], all_object[i].trans[2]))
					*glm::rotate(glm::mat4(1.0f), all_object[i].rot[0] * 3.1415926f / 180.0f, glm::vec3(1, 0, 0))
					*glm::rotate(glm::mat4(1.0f), all_object[i].rot[1] * 3.1415926f / 180.0f, glm::vec3(0, 1, 0))
					*glm::rotate(glm::mat4(1.0f), all_object[i].rot[2] * 3.1415926f / 180.0f, glm::vec3(0, 0, 1))
					*glm::scale(glm::mat4(1.0f), glm::vec3(all_object[i].scale[0], all_object[i].scale[1], all_object[i].scale[2]));			

				if (all_object[i].have_texture == true)
				{
					prog["have_texture"] = 1;
					all_object[i].color = glm::vec3{ 1.0f };
					prog["text"] = i;
					T[all_object[i].text-1].bindToChannel(i);
					all_object[i].color = glm::vec3(1.0f,1.0f,1.0f);
				}
				else
				{
					prog["have_texture"] = 0;

				}
				
				prog["object_color"] = all_object[i].color;
	
				prog.use();
					S[all_object[i].shape - 1].draw();

					
			}
			
			
			glDisable(GL_DEPTH_TEST);

			Gui();
			
			
			
			
			
			glfwSwapBuffers(window);

		}


	}
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


