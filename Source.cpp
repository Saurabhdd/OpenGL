#include<windows.h>
#include<stdio.h>
#include<math.h>
#include<gl/gl.h>
#include<gl/GLU.h>
#include"Header.h"
#include"Math3d.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "Winmm.lib")

#define GL_PI 3.14159
#define WINWIDTH 800
#define WINHEIGHT 600

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

FILE *gbFile = NULL;
FILE *gbFile_SSD = NULL;
HWND ghwnd;
bool gbActiveWindow = false;
bool gbFullScreen = false;
bool unitialize = false;

HGLRC hglrc;
HDC ghdc;
DWORD dwStyle;
WINDOWPLACEMENT wPrev;
int WINDOWMAXWIDTH, WINDOWMAXHEIGHT, X, Y;

GLfloat complete_cut_scene = false;

GLfloat flapping_S5 = 0.50f;
GLfloat birdYTrans_S5 = -0.51f;
GLfloat headPos_S5 = 0.0f;
GLfloat headPosY_S5 = 0.0f;
GLfloat leftWalkAngle_S5 = 0.0f;
GLfloat birdForwardMovement_S5 = 0.0f;
GLfloat rightWalkAngle_S5 = 0.0f;
GLfloat xAngle_S5 = 0.0f;

static GLfloat wingsFlap_S5 = 0.0f;
static GLfloat sideWingFlap_S5 = 0.0f;
static GLfloat lowerWingsFlap_S5 = 0.0f;
static GLfloat sideLowerWingFlap_S5 = 0.0f;

GLUquadric *quadric_SSD = NULL;

GLfloat cameraXS2_S5 = 0.00000f;//1.8
GLfloat cameraYS2_S5 = 0.0f;//0.4
GLfloat cameraZS2_S5 = 5.00003f;//0.1
GLfloat cameraUpZS2_S5 = 0.0f;
GLfloat cameraUpYS2_S5 = 1.0f;
GLfloat cameraCenterYS2_S5 = 0.0f;

GLfloat cameraZS3_S5 = 5.999997f;

 GLfloat fogColorChange_S5 = 0.5f;
 GLfloat fogStart_S5 = 3.0f;
 GLfloat fogEnd_S5 = 13.0f;

GLuint texture_rock_S5;
GLuint texture_door_S5;
GLuint texture_brick_S5;
GLuint texture_grass_S5;
GLuint texture_sky_S5;
GLuint side_texture_S5;
GLuint stem_texture_S5;
GLuint texture_lightning_S5;
GLuint texture_feather_S5;
GLuint mahadev_tex_S5;
GLuint trishul_tex_S5;

//-18.400002, lightningY=51.400002, lightningZ=-40.299999
//light calculations
GLfloat lightPosX_S5 = -18.400002f;
GLfloat lightPosY_S5 = 51.400002f;
GLfloat lightPosZ_S5 = -40.299999f;

bool endScene_S5 = false;
bool startDarkness_S5 = true;

//end scene calculations
//divineLightcalculations X=-0.200000, Y=-2.000000, Z=-2.500000
GLfloat DivLightUY = 22.0f;
GLfloat DivLightLX = -55.0f;
GLfloat DivLightFLZ = 0.50f;
GLfloat DivLightRX = -54.0f;//-8
GLfloat DivLightLY = 21.80f;//1.3
GLfloat DivLightFRZ = 0.60f;//2.0
GLfloat DivLightBRZ = -0.60f;//-2.0
GLfloat DivLightBLZ = -0.50f;

GLfloat DivLightX = -0.20f;
GLfloat DivLightY = -2.0f;
GLfloat DivLightZ = -2.50f;

//trishul calculation
GLfloat xFurther = 0.0f;
GLfloat yFurther = 0.0f;
GLfloat zFurther = 0.0f;

///////////////////////////////////////////////////////////////////////
//scene2 variables***************************************************
GLint counter_scene2 = 0;
GLfloat xAngle_scene2 = 0.0f;
GLfloat xTrans_scene2 = 11.799f;
GLfloat yTrans_scene2 = -1.0f;
GLfloat zTrans_scene2 = -1.6f;

//human variables
GLfloat leftWalkAngleHuman = 0.0f;
GLfloat rightWalkAngleHuman = 0.0f;
GLfloat rightWalkAngleHandHuman = 0.0f;
GLfloat leftWalkAngleHandHuman = 0.0f;

GLfloat yRot_scene2 = 295.0f;
bool sit = false;

GLfloat cameraX_scene2 = 0.0f;
GLfloat cameraY_scene2 = -0.20f;
GLfloat cameraZ_scene2 = 3.0f;

//bird variables
GLfloat flappingBird = 0.50f;
GLfloat birdYTransBird = -0.51f;
GLfloat headPosBird = 0.0f;
GLfloat headPosYBird = 0.0f;
GLfloat leftWalkAngleBird = 0.0f;
GLfloat birdForwardMovementBird = 0.0f;
GLfloat rightWalkAngleBird = 0.0f;
GLfloat yAngle_scene2 = 0.0f;
GLfloat birdBackwardMovementBird = 0.0f;
GLfloat birdYMovement = 0.20f;
GLfloat birdXMovement = -4.50f;

//texture
GLuint nature_texture;
GLuint nature1_texture;


bool scene1Completed = false;

////////////////////////////////////////////////////////////
//scene 1 variables**********************************************
GLfloat COORDINATE[3];
static GLfloat lightXPos_scene1 = -7.599995f;
static GLfloat lightZPos_scene1 = -13.500015f;
static GLfloat lightYPos_scene1 = 13.000013f;

GLfloat yRot_scene1 = 0.0f;
GLuint texture_sky_scene1;

GLint counter_scene1 = 0;
//GLfloat xAngle = 0.0f;
GLfloat xTrans_scene1 = 11.799f;
GLfloat yTrans_scene1 = -1.6f;
GLfloat zTrans_scene1 = -1.6f;


GLfloat humanDisplacementZ_scene1_human1 = -4.02;
GLfloat humanDisplacementY_scene1_human1 = -1.66f;
GLfloat humanDisplacementX_scene1_human1 = 0.0f;


GLfloat humanDisplacementZ_scene1_human2 = -4.02;
GLfloat humanDisplacementY_scene1_human2 = -1.3f;
GLfloat humanDisplacementX_scene1_human2 = 0.0f;

GLfloat yRothuman_scene1 = 295.0f;

GLfloat leftWalkAngleHuman_scene1 = 0.0f;
GLfloat rightWalkAngleHuman_scene1 = 0.0f;
GLfloat rightWalkAngleHandHuman_scene1 = 0.0f;
GLfloat leftWalkAngleHandHuman_scene1 = 0.0f;
bool sit_scene1 = false;
bool camerAfterBirdFall = false;

//temporary
GLfloat zRotate_scene1 = 7.0f;
GLfloat xRotate_scene1 = 0.0f;
GLfloat yRotate_scene1 = 0.0f;

//variables for audio files
int start_poem_counter = 0;
int start_mahadev_song_counter = 0;
int start_air_sound_counter = 0;
int start_interrupt_sound_counter = 0;
int start_tandav_song_counter = 0;
int start_interrupt_2_sound_counter = 0;
int start_lightning_sound_counter = 0;
int start_falling_sound_counter = 0;
int start_sunset_song_counter = 0;
int start_title_track_counter = 0;
int start_second_track = 0;
int start_TITLE_track_counter = 0;

//title and end credit
GLuint text_title_1;
GLuint text_title_2;
GLuint text_title_3;
GLuint text_ECredit_1;
GLuint text_ECredit_2;
GLuint text_ECredit_3;

 bool title = true;

 bool theEnd = false;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Function declaration
	void Display(void);
	void Initialize(void);

	//variable declaration
	HWND hwnd;
	bool bDone = false;
	TCHAR szAppName[] = TEXT("MyWIndow");
	WNDCLASSEX wndclass;
	MSG msg;

	//Creation of the log file
	if (fopen_s(&gbFile, "logApp.txt", "w"))
	{
		MessageBox(NULL, TEXT("Log file creation unsuccessful, exiting"), TEXT("Error"), MB_OK);
		exit(0);
	}

	if (fopen_s(&gbFile_SSD, "logApp1.txt", "w"))
	{
		MessageBox(NULL, TEXT("Log file creation unsuccessful, exiting"), TEXT("Error"), MB_OK);
		exit(0);
	}

	wPrev = { sizeof(WINDOWPLACEMENT) };

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClassEx(&wndclass);

	WINDOWMAXWIDTH = GetSystemMetrics(SM_CXMAXIMIZED);
	WINDOWMAXHEIGHT = GetSystemMetrics(SM_CYMAXIMIZED);

	X = (WINDOWMAXWIDTH / 2) - (WINWIDTH / 2);
	Y = (WINDOWMAXHEIGHT / 2) - (WINHEIGHT / 2);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName, TEXT("practice"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		X, Y,
		WINWIDTH,
		WINHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	Initialize();
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				Display();
			}
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ToggleFullScreen(void);
	void Uninitialize(void);
	void Resize(int, int);
	void ChangeDisplay(void);
	//void Display(void);

	switch (iMsg)
	{


	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;

	case WM_ERASEBKGND:
		return 0;

	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CHAR:
		switch (wParam)
		{

		case 'x':
			xFurther -= 0.1f;
			break;

		case 'X':
			xFurther += 0.1f;
			break;

		case 'y':
			yFurther -= 0.1f;
			break;

		case 'Y':
			//walkAngle += 7.0f;
			yFurther += 0.1f;
			break;

		case 'z':
			zFurther -= 0.1f;
			break;

		case 'Z':
			zFurther += 0.1f;
			break;

		
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);


		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;

		default:
			break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_PAINT:
		//Display();
		break;



	case WM_DESTROY:
		Uninitialize();
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}

void ToggleFullScreen(void)
{
	//local variable declaration
	MONITORINFO mi = { sizeof(MONITORINFO) };
	//code

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE); //getWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~WS_OVERLAPPEDWINDOW));

				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, (mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED);  //SetWindowPosition(ghwnd, HWND_TOP, mi.rcmonitor.left, mi.rcMonitor.top, (mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED); //WM_NCCALCSIZE

			}
		}

		ShowCursor(FALSE);
		gbFullScreen = true;
	}

	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
		gbFullScreen = false;
	}

}

void Initialize()
{
	//function declaration
	void Resize(int, int);
	bool LoadTexture(GLuint *, TCHAR[]);

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		fprintf_s(gbFile, "choosepixel()  failed\n");
		DestroyWindow(ghwnd);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf_s(gbFile, "SetPixel()  failed\n");
		DestroyWindow(ghwnd);
	}

	hglrc = wglCreateContext(ghdc);
	if (hglrc == NULL)
	{
		fprintf_s(gbFile, "wglCreateContext()  failed\n");
		DestroyWindow(ghwnd);
	}

	if (wglMakeCurrent(ghdc, hglrc) == FALSE)
	{
		fprintf_s(gbFile, "wglMakeCurrent()  failed\n");
		DestroyWindow(ghwnd);
	}

	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glColor3f(0.0f, 1.0f, 0.0f);
	//glShadeModel(GL_FLAT);
	//glFrontFace(GL_CW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	LoadTexture(&texture_grass_S5, MAKEINTRESOURCE(GRASS));
	LoadTexture(&texture_brick_S5, MAKEINTRESOURCE(MY_BRICK));
	LoadTexture(&texture_sky_S5, MAKEINTRESOURCE(SKY));
	LoadTexture(&side_texture_S5, MAKEINTRESOURCE(SIDETEXT));
	LoadTexture(&stem_texture_S5, MAKEINTRESOURCE(STEM));
	LoadTexture(&texture_lightning_S5, MAKEINTRESOURCE(LIGHTNING));
	LoadTexture(&texture_rock_S5, MAKEINTRESOURCE(MY_WOOD));
	LoadTexture(&texture_door_S5, MAKEINTRESOURCE(MY_DOOR));
	LoadTexture(&texture_feather_S5, MAKEINTRESOURCE(FEATHER));
	LoadTexture(&mahadev_tex_S5, MAKEINTRESOURCE(MAHADEV));
	LoadTexture(&trishul_tex_S5, MAKEINTRESOURCE(TRISHUL));
	LoadTexture(&nature_texture, MAKEINTRESOURCE(NATURE));
	LoadTexture(&nature1_texture, MAKEINTRESOURCE(NATURE1));
	LoadTexture(&text_title_1, MAKEINTRESOURCE(TITLE1));
	LoadTexture(&text_title_2, MAKEINTRESOURCE(TITLE2));
	LoadTexture(&text_ECredit_1, MAKEINTRESOURCE(ENDCREDIT1));
	LoadTexture(&text_ECredit_2, MAKEINTRESOURCE(ENDCREDIT2));
	LoadTexture(&text_ECredit_3, MAKEINTRESOURCE(ENDCREDIT3));

	Resize(WINWIDTH, WINHEIGHT);

}

void Resize(int width, int height)
{
	if (height <= 0) {
		height = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);

}

void Display(void)
{
	void Display_1(bool*);
	void Display_2(bool *);
	void Display_3(bool*);
	bool LoadTexture(GLuint *, TCHAR[]);
	void TitleAndEndCredits(int);


	static bool scene_2 = false;
	static bool scene_1 = false;
	static bool scene_3 = false;
	static GLint counter = 1;

	static GLfloat counter_end = 0.0f;
	
	start_TITLE_track_counter++;

	if (start_second_track == 1)
		PlaySound(MAKEINTRESOURCE(POEM), NULL, SND_RESOURCE | SND_ASYNC);
 
	if (start_air_sound_counter == 1)
		PlaySound(MAKEINTRESOURCE(AIR_SOUND), NULL, SND_RESOURCE | SND_ASYNC);

	if (start_lightning_sound_counter == 1)
		PlaySound(MAKEINTRESOURCE(LIGHTNING_SOUND), NULL, SND_RESOURCE | SND_ASYNC);

	if (start_TITLE_track_counter == 1)
		PlaySound(MAKEINTRESOURCE(TITLE_TRACK), NULL, SND_RESOURCE | SND_ASYNC);

	
		if (title)
			TitleAndEndCredits(1);
		else
		{
			if (!scene_1)
				Display_1(&scene_1);
			else if (!scene_2)
				Display_2(&scene_2);
			else
				Display_3(&scene_3);
		}

		if (scene_3)
			TitleAndEndCredits(2);
	
	
	
	
	SwapBuffers(ghdc);

}

void TitleAndEndCredits(int check)
{
	static GLfloat title_1_Z = -6.50f;
	static GLfloat title_2_Z = -3.70f;
	static GLfloat endCredit_1_Z = -3.50f;
	static GLfloat endCredit_2_Z = -3.50f;
	static GLfloat endCredit_3_Z = -3.50f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();

	glPushMatrix();

	if (check == 1)
	{
		if (title_1_Z <= 0.0f)
		{
			glTranslatef(0.0f, 0.0f, title_1_Z);
			title_1_Z += 0.001f;
			glBindTexture(GL_TEXTURE_2D, text_title_1);
		}
		else if(title_2_Z <= -3.0f)
		{
			start_title_track_counter++;
			glTranslatef(0.20f, 0.0f, title_2_Z);
			title_2_Z += 0.0001f;
			glBindTexture(GL_TEXTURE_2D, text_title_2);
		}
		else
			title = false;
	}

	if (check == 2)
	{
		if (endCredit_1_Z <= -3.0f)
		{
			glTranslatef(0.0f, 0.0f, endCredit_1_Z);
			endCredit_1_Z += 0.001f;
			glBindTexture(GL_TEXTURE_2D, text_ECredit_1);
		}
		else if (endCredit_2_Z <= -3.0f)
		{
			glTranslatef(0.0f, 0.0f, endCredit_2_Z);
			endCredit_2_Z += 0.001f;
			glBindTexture(GL_TEXTURE_2D, text_ECredit_2);
		}
		else if (endCredit_3_Z <= -3.0f)
		{
			glTranslatef(0.0f, 0.0f, endCredit_3_Z);
			endCredit_3_Z += 0.001f;
			glBindTexture(GL_TEXTURE_2D, text_ECredit_3);
		}
		else if (endCredit_3_Z <= -2.7f)
		{
			endCredit_3_Z += 0.001f;
			theEnd = true;
		}else
			DestroyWindow(ghwnd);
	}

	if (!theEnd)
	{
		glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-2.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, -1.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 1.0f, 0.0f);
		glEnd();

	}
	
	glPopMatrix();
}

void Display_3(bool *scene_completed)
{
	//function declaration
	void DrawGround_S5(GLint);
	void DrawHome_S5(bool);
	void DrawTree_S5(bool, GLint);
	void sideTexture_S5(void);
	void Scene_S5(bool*, GLint, bool *, bool, bool, bool*);
	void Display_1(bool*);
	//void Scene3(bool *, GLint, bool*);

	//flapping of wings


	//scene variables
	static bool scene1 = false;
	static bool scene2 = false;
	static bool scene2Cut = false;
	static bool scene3 = false;
	static bool scene4 = false;
	static bool birdTransStart = false;
	static bool cutSceneCompleted = false;
	static bool scene_cut = false;

	static GLint birdNegativeXPassCounter = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();

	if (nature_texture)
	{
		glDeleteTextures(1, &nature_texture);
	}

	if (nature1_texture)
	{
		glDeleteTextures(1, &nature1_texture);
	}


	//changes in scene1
	//zRotate=0.009887, xRotate=-0.000294, yRotate=0.001398
	zRotate_scene1 = 0.009887f;
	xRotate_scene1 = -0.000294f;
	yRotate_scene1 = 0.001398f;

	if (scene2 && scene3)
		gluLookAt(cameraXS2_S5, cameraYS2_S5, cameraZS2_S5, 0.0f, 0.0f, 0.0f, 0.0f, cameraUpYS2_S5, cameraUpZS2_S5);
	else
		glTranslatef(0.0f, 0.0f, -5.0f);

	if (scene2Cut && !complete_cut_scene)
	{
		Display_1(&scene_cut);
		camerAfterBirdFall = true;
	}

	if(scene2Cut && scene_cut)
		cutSceneCompleted = true;

	if (birdForwardMovement_S5 <= -5.477774f && !endScene_S5)
	{
		birdForwardMovement_S5 = 4.0f;
		birdNegativeXPassCounter++;

	}
	if (birdNegativeXPassCounter == 1)
		scene2 = true;

	if (birdNegativeXPassCounter == 2)
		scene3 = true;


	//fprintf_s(gbFile, "birdNegativePaassCounter=%d, birdForwardMovement=%f\n", birdNegativeXPassCounter, birdForwardMovement);

	if (!scene2)
	{
		fogStart_S5 = 15.0f;
		fogEnd_S5 = 40.0f;
		fogColorChange_S5 = 0.05f;
		Scene_S5(&scene2Cut, 2, &scene2, birdTransStart, cutSceneCompleted, scene_completed);
	}
	else
	{
		fogStart_S5 = 3.0f;
		fogEnd_S5 = 13.0f;
		fogColorChange_S5 = 0.5f;

		if (!scene3)
		{
			glTranslatef(0.0f, 0.0f, cameraZS3_S5);
			Scene_S5(&scene2Cut, 3, &scene3, birdTransStart, cutSceneCompleted, scene_completed);

			if (cameraZS3_S5 >= 0.0f)
				cameraZS3_S5 -= 0.01f;
			if (cameraZS3_S5 <= 1.0f)
				birdTransStart = true;
		}
		else
		{
			Scene_S5(&scene2Cut, 4, &scene4, birdTransStart, cutSceneCompleted, scene_completed);
		}

	}


}

void Scene_S5(bool* completed, GLint sceneNumber, bool *sceneCompleted, bool birdTransStart, bool cutSceneCompleted, bool *sceneComplete)
{
	//function declaration
	void DrawTree_S5(bool, GLint);
	void DrawTree__S5(bool, GLint);
	void BirdModel_S5(bool);
	void WingsFlapping_S5(GLint*, bool*, bool*, bool*, bool*, GLfloat);
	void Walk_S5(bool, GLfloat);
	void Fly_S5(GLint*, bool, GLfloat, GLfloat);
	void Fall_S5(bool *);
	void DrawGround_S5(GLint);
	void DrawTower_S5(bool);
	void DrawHome_S5(bool);

	static GLint counter = 0;

	//variable declaration
	static bool flappingFlag = true;
	static bool walk = false;
	static GLfloat travel = 0.0f;
	static bool fall = false;
	static bool getUp = false;
	static GLfloat flyDirection = 20.0f;
	static bool fallDone = false;
	static bool fallStart = false;
	static bool lightNingStart = false;
	static bool branchfall = false;
	static bool startFlappingAgain = false;

	static GLfloat afterFallAngleY = 0.0f;
	static GLfloat afterFallAngleZ = 0.0f;
	static GLfloat forwadMovementDecrementAfterFall = 0.0071f;
	static GLfloat forwadMovementDecrementAfterFall_delay = 0.0071f;
	static GLfloat branchFall = 2.0f;
	static GLfloat birdZTrans = 0.0f;
	static GLint onceCounter = 0;
	

	

	//lighting variables
	//-28.500002f, 71.800003f, -30.200003f
	//-18.400002, lightningY=51.400002, lightningZ=-40.299999
	

	GLfloat lightPos[] = { lightPosX_S5, lightPosY_S5, lightPosZ_S5, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	M3DVector3f vNormal;
	M3DVector3f vPoints[3];
	M3DVector3f shadowPointsTree[3] = { {-5.20f , -1.170f, -5.20f },
								  {-5.20f , -1.170f, 5.20f },
								  {5.20f , -1.170f, 5.20f} };

	M3DVector3f shadowPointsBird[3] = { {-2.0f * 1.2f,-2.50f, -2.0f * 1.2f},
								  {-2.0f * 1.2f, -2.50f, 2.0f * 1.2f},
								  {2.0f * 1.2f, -2.50f, 2.0f * 1.2f} };

	M3DVector4f vPlaneEquationTree;
	M3DMatrix44f vShadowMatrixTree;
	M3DVector4f vPlaneEquationBird;
	M3DMatrix44f vShadowMatrixBird;

	M3DVector3f shadowPoints[3] = { {-2.0f * 0.7f, -1.30f * 0.7f, -2.0f * 0.7f},
								  {-2.0f * 0.7f, -1.30f * 0.7f, 2.0f * 0.7f},
								  {2.0f * 0.7f, -1.30f * 0.7f, 2.0f * 0.7f} };

	M3DVector3f shadowPointsHome[3] = { {-2.0f * 1.2f, -1.300f * 1.2f, -2.0f * 1.2f},
								  {-2.0f * 1.2f, -1.30f * 1.2f, 2.0f * 1.2f},
								  {2.0f * 1.2f, -1.30f * 1.2f, 2.0f * 1.2f} };
	M3DVector4f vPlaneEquation;
	M3DMatrix44f vShadowMatrix;
	M3DVector4f vPlaneEquationHome;
	M3DMatrix44f vShadowMatrixHome;
	
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	m3dGetPlaneEquation(vPlaneEquationTree, shadowPointsTree[0], shadowPointsTree[1], shadowPointsTree[2]);

	m3dMakePlanarShadowMatrix(vShadowMatrixTree, vPlaneEquationTree, lightPos);

	m3dGetPlaneEquation(vPlaneEquation, shadowPoints[0], shadowPoints[1], shadowPoints[2]);

	m3dMakePlanarShadowMatrix(vShadowMatrix, vPlaneEquation, lightPos);

	m3dGetPlaneEquation(vPlaneEquationHome, shadowPointsHome[0], shadowPointsHome[1], shadowPointsHome[2]);

	m3dMakePlanarShadowMatrix(vShadowMatrixHome, vPlaneEquationHome, lightPos);

	//enabling fog

	/*if (sceneNumber == 2)
	{
		
	}
	if (sceneNumber == 3)
	{
		
	}*/

	if (birdForwardMovement_S5 <= -21.0f)
		*sceneComplete = true;

	GLfloat fogColor[] = { fogColorChange_S5, fogColorChange_S5, fogColorChange_S5, 1.0f };//0.05

	if (sceneNumber != 4)
	{
        glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_START, fogStart_S5);//15
		glFogf(GL_FOG_END, fogEnd_S5);//40
		glFogi(GL_FOG_MODE, GL_LINEAR);
	}
	else
		glDisable(GL_FOG);

	//fprintf_s(gbFile, "lightCalculations, x=%f, y=%f, z=%f\n", lightPosX, lightPosY, lightPosZ);

	//fog calculations
	/*if (fogColorChange >= 0.05f)
		fogColorChange -= 0.0005f;

	if (fogStart <= 15.0f)
		fogStart += 0.05f;

	if (fogEnd <= 40.0f)
		fogEnd += 0.05f;
	else*/
		startFlappingAgain = true;
	/*m3dGetPlaneEquation(vPlaneEquationBird, shadowPointsBird[0], shadowPointsBird[1], shadowPointsBird[2]);

	m3dMakePlanarShadowMatrix(vShadowMatrixBird, vPlaneEquationBird, lightPos);*/

	
			glPushMatrix();
			DrawGround_S5(sceneNumber);
			glPopMatrix();
		

	

	//shadows *******************************
	
	if (sceneNumber == 2)
	{
		//firstly creating shadow for tree
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glPushMatrix();

		glMultMatrixf((GLfloat *)vShadowMatrixTree);
		glTranslatef(4.0f, 0.0f, -5.0f);
		DrawTree_S5(true, 5);

		glPopMatrix();
	}
	

	//Tree*******************************************
	
	if (sceneNumber == 2)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		glPushMatrix();

		glTranslatef(4.0f, 0.0f, -5.0f);

		DrawTree_S5(false, 5);

		glPopMatrix();

		glPushMatrix();

		if (lightNingStart)
			branchfall = true;

		if (branchfall && branchFall >= -1.5f)
			branchFall -= 0.1f;

		glTranslatef(3.0f, branchFall, -5.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		quadric_SSD = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, stem_texture_S5);
		gluQuadricTexture(quadric_SSD, true);
		gluCylinder(quadric_SSD, 0.04f, 0.042f, 0.8f, 10, 10);

		glPopMatrix();

	}
	
	//bird*****************************
	
	if (sceneNumber == 2)
	{
		glPushMatrix();
		//glTranslatef(0.0f, 0.0f, -5.0f);
		//glRotatef(50.0f,0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, birdYTrans_S5, 0.0f);
		glTranslatef(birdForwardMovement_S5, 0.0f, 0.0f);
		glTranslatef(flyDirection, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(afterFallAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(afterFallAngleZ, 1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);

		fprintf_s(gbFile, "forwardMovement=%f\n", birdForwardMovement_S5);
		//
		if (fallDone)
		{
			if (birdForwardMovement_S5 >= -2.004792f)
				birdForwardMovement_S5 -= forwadMovementDecrementAfterFall;

			if (forwadMovementDecrementAfterFall >= 0.0f)
				forwadMovementDecrementAfterFall -= 0.000015f;
			else
				*completed = true;

			if (birdForwardMovement_S5 <= -1.419376f)
				start_second_track++;

			fprintf_s(gbFile_SSD, "birdForwardMovement*************%f\n", forwadMovementDecrementAfterFall);
		}

		//fprintf_s(gbFile, "birdfallX=%f\n", birdForwardMovement);

		if (fallDone == false)
			Fly_S5(&counter, fallStart, 2.5f, 1.0f);

		fprintf_s(gbFile, "flyDirection=%f\n", flyDirection);

		glRotatef(25.0f, 1.0f, 0.0f, 0.0f);

		BirdModel_S5(walk);

		//Walk(walk);

		if (flyDirection <= 2.769880f)
		{
			if (flyDirection >= 2.5f)
			{
				lightNingStart = true;
				start_lightning_sound_counter++;
			}
			else
				lightNingStart = false;

			fallStart = true;

			walk = true;

			if (birdYTrans_S5 >= -0.51f && !fallDone)
			{
				birdYTrans_S5 -= 0.03f;
			}
			else {
				fallDone = true;
				fallStart = false;
				afterFallAngleY = 20.0f;
				afterFallAngleZ = -15.0f;

			}

		}

		counter += 5;

		if (!fallDone)
			flyDirection -= 0.03f;

		if (counter == 1000000)
			counter = 0;

		if (*completed == true && sceneNumber == 2 && cutSceneCompleted)
		{
			WingsFlapping_S5(&counter, &flappingFlag, &walk, &fall, &getUp, 20.0f);
			//fprintf_s(gbFile, "flapping while scene2=%f, birdForwardMovement=%f\n", flapping, birdForwardMovement);
			Walk_S5(walk, 20.0f);
			afterFallAngleZ = 0.0f;
			afterFallAngleY = 0.0f;
			start_poem_counter++;

			if (onceCounter == 1)
				headPos_S5 = 0.0f;

			onceCounter++;
			if (onceCounter >= 100)
				onceCounter = 2;
		}

		glPopMatrix();

	}

	//bird in scene 4 ****************************
	if (sceneNumber == 4)
	{
		flappingFlag = true;
		flapping_S5 = 10.5f;
		walk = true;
		if(birdForwardMovement_S5 >= 0.0f)
		   birdYTrans_S5 = -0.50f;

		if (birdForwardMovement_S5 < 1.40f)
			start_mahadev_song_counter++;

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		//glRotatef(50.0f,0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, birdYTrans_S5, 0.0f);
		glTranslatef(birdForwardMovement_S5, 0.0f, birdZTrans);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.4f, 0.4f, 0.4f);

		fprintf_s(gbFile, "BirdYDirection=%f\n", birdYTrans_S5);
		wingsFlap_S5 = 10.0f;
		sideWingFlap_S5 = -7.5f;

		/*if (birdForwardMovement <= 5.5f && cameraYS2 >= -0.9f)
			startDarkness = true;*/

		if (birdForwardMovement_S5 <= 1.5f)
		{

			if (cameraZS2_S5 >= -5.0f)//cameraX=4.397843, cameraZ=0.602067
			{
				if (cameraXS2_S5 <= 4.39f)
				{
					if (endScene_S5)
					{
						cameraZS2_S5 -= 0.01f;
						cameraXS2_S5 += 0.01f;

						if(cameraYS2_S5 >= -0.9f)
						cameraYS2_S5 -= 0.01f;
					}
					else
					{
						cameraZS2_S5 -= 0.01f;
						cameraXS2_S5 += 0.01f;
						//cameraYS2 += 0.004f;
					}

				}
				
				if (cameraZS2_S5 <= 4.5f)
					endScene_S5 = true;

				fprintf_s(gbFile, "cameraX=%f, cameraZ=%f, cameraY=%f\n", cameraXS2_S5, cameraZS2_S5, cameraYS2_S5);
			}

			if (!startDarkness_S5)
			{
				if (birdForwardMovement_S5 <= 2.0f)
					Walk_S5(walk, 0.8f);
				else
				    Walk_S5(walk, 0.80f);
			}
			
			else
			{
				Fly_S5(&counter, fall, 40.0f, 4.50f);
			}
				
			if (birdForwardMovement_S5 <= 0.0f)
			{
				birdForwardMovement_S5 -= 0.01f;
				birdYTrans_S5 += 0.002f;
				wingsFlap_S5 = 10.0f;
				sideWingFlap_S5 = -7.0f;
				birdZTrans -= 0.0025f;

			}

			//walk = false;
		}	
		else
		{
			WingsFlapping_S5(&counter, &flappingFlag, &walk, &fall, &getUp, 20.0f);
			Walk_S5(walk, 35.0f);
		}

		fprintf_s(gbFile, "wingsangle first=%f, seconf=%f\n", wingsFlap_S5, sideWingFlap_S5);
		glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

		if(birdForwardMovement_S5 >= -11.019530f)
		BirdModel_S5(walk);
		counter ++;

		if (counter == 1000000)
			counter = 0;

		//fprintf_s(gbFile, "forwardmovement=%f, and yTrans=%f\n", birdForwardMovement, birdYTrans);
		glPopMatrix();
	}
	
	//scene4 end scene**********************************
	if (sceneNumber == 4 && cameraYS2_S5 <= -0.9f)
	{
		glPushMatrix();
		glTranslatef(DivLightX, DivLightY, DivLightZ);
		//code for flying of bird towards shiva
		//glBindTexture(GL_TEXTURE_2D, white_texture);
		glBegin(GL_QUADS);
		glVertex3f(DivLightLX, DivLightUY, DivLightFLZ);
		glVertex3f(DivLightRX, DivLightLY, DivLightFRZ);
		glVertex3f(DivLightRX, DivLightLY, DivLightBRZ);
		glVertex3f(DivLightLX, DivLightUY, DivLightBLZ);
		glEnd();
		glPopMatrix();
		
		//condition for divine light coming to take bird
		//forwardmovement=0.281654, and yTrans=-0.496000
		/*GLfloat DivLightRX = -54.0f;//-8
GLfloat DivLightLY = 21.80f;//1.3
GLfloat DivLightFRZ = 0.60f;//2.0
GLfloat DivLightBRZ = -0.60f;//-2.0*/
		if (birdForwardMovement_S5 <= 0.281654f && birdForwardMovement_S5 >= -11.019530f)
		{
			if (DivLightRX <= -8.0f)
				DivLightRX += 0.09f;

			if (DivLightLY >= 1.3f)
				DivLightLY -= 0.04f;

			if (DivLightFRZ <= 2.0f)
				DivLightFRZ += 0.04f;

			if (DivLightBRZ >= -2.0f)
				DivLightBRZ -= 0.04f;
		}

		if (birdForwardMovement_S5 <= -11.019530f)
		{
			if (DivLightRX >= -55.0f)
				DivLightRX -= 0.09f;

			if (DivLightLY <= 22.0f)
				DivLightLY += 0.04f;

			if (DivLightFRZ >= -0.5f)
				DivLightFRZ -= 0.04f;

			if (DivLightBRZ >= -0.5f)
				DivLightBRZ += 0.04f;

		}
		fprintf_s(gbFile, "divineLightcalculations X=%f*************************\n",birdForwardMovement_S5);
	}

	
	//bird in scene3********************************

	if (sceneNumber == 3 && birdTransStart == true)
	{
		flappingFlag = true;
		walk = true;
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
		//glRotatef(50.0f,0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, birdYTrans_S5, 0.0f);
		glTranslatef(birdForwardMovement_S5, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);

		if (sceneNumber == 3 && (birdForwardMovement_S5 >= 3.50f || birdForwardMovement_S5 <= -2.5f))
		{
			WingsFlapping_S5(&counter, &flappingFlag, &walk, &fall, &getUp, 30.0f);
			Walk_S5(walk, 55.0f);
		}

		if (sceneNumber == 3 && !((birdForwardMovement_S5 >= 3.50f || birdForwardMovement_S5 <= -2.5f)))
		{
			Fly_S5(&counter, fall, 30.0f, 45.0f);
		}

		//fprintf_s(gbFile, "x=%f, y=%f, z=%f\n", cameraXS2, cameraYS2, cameraZS2);

		if (birdForwardMovement_S5 < -2.5f)
			fprintf_s(gbFile, "flapping=%f, and birdForward=%f\n", flapping_S5, birdForwardMovement_S5);

		

		glRotatef(25.0f, 1.0f, 0.0f, 0.0f);

		BirdModel_S5(walk);
		
		counter += 5;

		if (counter == 1000000)
			counter = 0;

		glPopMatrix();

	}

	//shadow for home and tower**********************
	//creating shadow

	if (sceneNumber == 5)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glPushMatrix();

		glTranslatef(4.0f, 0.0f, -6.0f);
		glMultMatrixf((GLfloat *)vShadowMatrix);

		DrawTower_S5(true);

		glPopMatrix();

		//creating shadow for home
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glPushMatrix();

		glMultMatrixf((GLfloat *)vShadowMatrixHome);

		DrawHome_S5(true);

		glPopMatrix();

	}
	
	//another tree*************************************
	
	if (sceneNumber == 2)
	{
		glPushMatrix();

		glTranslatef(-4.50f, -1.0f, -25.0f);
		glRotatef(40.0f, 0.0f, 1.0f, 0.0f);

		DrawTree__S5(false, 6);

		glPopMatrix();
	}
	
	//creating model home and tower************************
	
	if (sceneNumber == 3)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		glPushMatrix();
		glTranslatef(4.0f, 0.0f, -6.0f);
		DrawTower_S5(false);

		glPopMatrix();

		//creating the model for home
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		glPushMatrix();

		glTranslatef(-6.50f, -0.3f, -2.0f);
		DrawHome_S5(false);

		glPopMatrix();
	}
	

	//tree for scene3****************
	if (sceneNumber == 3)
	{
		glPushMatrix();

		glTranslatef(-1.50f, -1.0f, -8.0f);
		glRotatef(40.0f, 0.0f, 1.0f, 0.0f);

		DrawTree__S5(false, 7);

		glPopMatrix();
	}

	//tree for scene3****************
	if (sceneNumber == 3)
	{
		glPushMatrix();

		glTranslatef(2.50f, -1.0f, -10.0f);
		glRotatef(40.0f, 0.0f, 1.0f, 0.0f);

		DrawTree__S5(false, 7);

		glPopMatrix();
	}

	//tree for scene3****************
	if (sceneNumber == 3)
	{
		glPushMatrix();

		glTranslatef(3.50f, -1.0f, 12.0f);

		DrawTree__S5(false, 5);

		glPopMatrix();
	}

	//tree for scene4****************
	if (sceneNumber == 4)
	{
		glDisable(GL_FOG);
		glPushMatrix();

		glTranslatef(0.0f, -1.0f, -9.0f);
		glRotatef(40.0f, 0.0f, 1.0f, 0.0f);

		DrawTree__S5(false, 7);

		glPopMatrix();
	}

	//second tree for scene4****************
	if (cameraYS2_S5 <= -0.9f && sceneNumber == 4)
	{
		glDisable(GL_FOG);
		glPushMatrix();

		glTranslatef(5.0f, -1.0f, -10.0f);
		glRotatef(40.0f, 0.0f, 1.0f, 0.0f);

		DrawTree_S5(false, 7);

		glPopMatrix();
	}

	//lightning*******************************************8
	glPushMatrix();

	glTranslatef(4.0f, 0.0f, -5.0f);
	glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
	glScalef(1.2f, 2.0f, 1.0f);
	if (lightNingStart)
	{
		if (!*completed)
			glTranslatef(-1.100000f, 1.0f, 0.100003f);//lightningX=-1.100000, lightningY=1.000000, lightningZ=0.100003

		else
			glTranslatef(-2.0f, 1.0f, .5f);

		glBindTexture(GL_TEXTURE_2D, texture_lightning_S5);
		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.4f, 0.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.3f, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.10f, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.3f, -1.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture_lightning_S5);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.4f, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.41f, -0.02f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.01f, -0.02f, 0.0f);
		glEnd();
	}
	//fprintf_s(gbFile, "lightningX=%f, lightningY=%f, lightningZ=%f\n", cameraXS2, cameraYS2, cameraZS2);

	glPopMatrix();
	
	fprintf_s(gbFile, "flapping=%f, sceneNumber=%d\n", flapping_S5, sceneNumber);

}

void sideTexture_S5(void)
{
	glBindTexture(GL_TEXTURE_2D, side_texture_S5);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-25.0f, 7.0f, 30.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-25.0f, -4.0f, 30.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-25.0f, -4.0f, -15.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-25.0f, 7.0f, -15.0f);

	glEnd();
}

void DrawTree_S5(bool shadow, GLint numberOfBranches)
{
	void DrawTreeBranch_S5(node *, GLfloat, bool shadow);
	node* InsertNode_S5(node*, GLfloat, GLfloat, GLfloat, GLint, GLint);
	void Uninitalize_tree(node*);

	static node* root = NULL;
	static node *root_val = NULL;
	static node *branch = NULL;
	static node *branch_val = NULL;
	static GLint root_counter = 1;
	static GLint branch_counter = 1;
	

	//freeing the memory which is already allocated while drawing the tree
	if (unitialize && root_val != NULL)
	{
		Uninitalize_tree(root_val->left);
		Uninitalize_tree(root_val->right);
		free(root_val);
		root_val = NULL;
	}

	else
	{
		if (root_counter == 1)
			root_val = InsertNode_S5(root, 0.0410f * 2.0f, 0.0810f * 2.0f, 0.8f * 2.0f, 0, numberOfBranches);

		root_counter++;
		if (root_counter == 100000)
		{
			root_counter = 2;
		}

		if (branch_counter == 1)
			branch_val = InsertNode_S5(branch, 0.04f, 0.08f, 0.5f, 0, numberOfBranches);

		branch_counter++;
		if (branch_counter == 100000)
		{
			branch_counter = 2;
		}


		glTranslatef(0.0f, -1.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(xAngle_S5, 0.0f, 0.0f, 1.0f);

		DrawTreeBranch_S5(root_val, 0.0f, shadow);

	}
	
	/*glPushMatrix();
	glTranslatef(0.0f, xTrans, 0.0f);

	fprintf_s(gbFile_SSD, "%f==xTrans\n", xTrans);

	glTranslatef(0.0f, 0.0f, yTrans);

	fprintf_s(gbFile_SSD, "%f==yTrans\n", yTrans);

	//glTranslatef(zTrans, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	DrawTreeBranch(branch_val, 0.0f);
	glPopMatrix();*/
}

void DrawTree__S5(bool shadow, GLint numberOfBranches)
{
	void DrawTreeBranch__S5(node *, GLfloat);
	node* InsertNode_S5(node*, GLfloat, GLfloat, GLfloat, GLint, GLint);
	void Uninitalize_tree(node*);

	static node* root = NULL;
	static node *root_val = NULL;
	static node *branch = NULL;
	static node *branch_val = NULL;
	static GLint root_counter = 1;
	static GLint branch_counter = 1;

	if (unitialize && root_val != NULL)
	{
		Uninitalize_tree(root_val->left);
		Uninitalize_tree(root_val->right);
		free(root_val);
		root_val = NULL;
	}
	else
	{
		if (root_counter == 1)
			root_val = InsertNode_S5(root, 0.0410f * 2.0f, 0.0810f * 2.0f, 0.8f * 2.0f, 0, numberOfBranches);

		root_counter++;
		if (root_counter == 100000)
		{
			root_counter = 2;
		}

		if (branch_counter == 1)
			branch_val = InsertNode_S5(branch, 0.04f, 0.08f, 0.5f, 0, numberOfBranches);

		branch_counter++;
		if (branch_counter == 100000)
		{
			branch_counter = 2;
		}

		/*quadric_SSD = gluNewQuadric();
		gluCylinder(quadric_SSD, 0.12f, 0.16f, 1.2f, 20, 20);
		quadric_SSD = gluNewQuadric();*/

		glTranslatef(0.0f, -1.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(xAngle_S5, 0.0f, 0.0f, 1.0f);

		DrawTreeBranch__S5(root_val, 0.0f);

	}


	
	/*glPushMatrix();
	glTranslatef(0.0f, xTrans, 0.0f);

	fprintf_s(gbFile_SSD, "%f==xTrans\n", xTrans);

	glTranslatef(0.0f, 0.0f, yTrans);

	fprintf_s(gbFile_SSD, "%f==yTrans\n", yTrans);

	//glTranslatef(zTrans, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	DrawTreeBranch(branch_val, 0.0f);
	glPopMatrix();*/
}

void Uninitalize_tree(node* tree)
{
	if (tree != NULL)
	{
		Uninitalize_tree(tree->left);
		Uninitalize_tree(tree->right);

		if(tree != NULL)
		free(tree);

		tree = NULL;
	}

}

void DrawTower_S5(bool drawShadow)
{
	//function declaration
	void SquareRod(GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, bool);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, -3.0f);
	glTranslatef(-1.0f, 0.0f, -1.0f);
	glScalef(0.7f, 0.7f, 0.7f);

	if (!drawShadow)
		glBindTexture(GL_TEXTURE_2D, texture_rock_S5);
	else
		glColor3f(0.0f, 0.0f, 0.0f);


	glBegin(GL_QUADS);
	glVertex3f(-0.7f, 0.50f, 0.6f);
	glVertex3f(-0.7f, 0.50f, -0.6f);
	glVertex3f(0.7f, 0.5f, -0.6f);
	glVertex3f(0.7f, 0.50f, 0.6f);

	glVertex3f(-0.7f, 0.5f, 0.6f);
	glVertex3f(-0.7f, 0.45f, 0.6f);
	glVertex3f(0.7f, 0.45f, 0.6f);
	glVertex3f(0.7f, 0.5f, 0.6f);


	glVertex3f(0.7f, 0.5f, 0.6f);
	glVertex3f(0.7f, 0.45f, 0.6f);
	glVertex3f(0.7f, 0.45f, -0.6f);
	glVertex3f(0.7f, 0.5f, -0.6f);


	glVertex3f(0.7f, 0.5f, -0.6f);
	glVertex3f(0.7f, 0.45f, -0.6f);
	glVertex3f(-0.7f, 0.45f, -0.6f);
	glVertex3f(-0.7f, 0.5f, -0.6f);

	glVertex3f(-0.7f, 0.5f, -0.6f);
	glVertex3f(-0.7f, 0.45f, -0.6f);
	glVertex3f(-0.7f, 0.45f, 0.6f);
	glVertex3f(-0.7f, 0.5f, 0.6f);

	glEnd();

	GLfloat leftLTop[3] = { -0.7f, 0.54f, 0.58f };
	GLfloat leftLBottom[3] = { -0.7f, 0.5f, 0.58f };
	GLfloat leftRBottom[3] = { -0.7f, 0.5f, 0.6f };
	GLfloat leftRTop[3] = { -0.7f, 0.54f, 0.6f };
	GLfloat rightLTop[3] = { 0.7f, 0.54f, 0.6f };
	GLfloat rightLBottom[3] = { 0.7f, 0.5f, 0.6f };
	GLfloat rightRBottom[3] = { 0.7f, 0.5f, 0.58f };
	GLfloat rightRTop[3] = { 0.7f, 0.54f, 0.58f };

	//railings 
	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[1] = 0.62f;
	leftLBottom[1] = 0.58f;
	leftRBottom[1] = 0.58f;
	leftRTop[1] = 0.62f;
	rightLTop[1] = 0.62f;
	rightLBottom[1] = 0.58f;
	rightRBottom[1] = 0.58f;
	rightRTop[1] = 0.62f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[1] = 0.7f;
	leftLBottom[1] = 0.66f;
	leftRBottom[1] = 0.66f;
	leftRTop[1] = 0.7f;
	rightLTop[1] = 0.7f;
	rightLBottom[1] = 0.66f;
	rightRBottom[1] = 0.66f;
	rightRTop[1] = 0.7f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	GLfloat leftLTopR[3] = { 0.7f, 0.54f, 0.58f };
	GLfloat leftLBottomR[3] = { 0.7f, 0.5f, 0.58f };
	GLfloat leftRBottomR[3] = { 0.7f, 0.5f, 0.6f };
	GLfloat leftRTopR[3] = { 0.7f, 0.54f, 0.6f };
	GLfloat rightLTopR[3] = { 0.7f, 0.54f, -0.6f };
	GLfloat rightLBottomR[3] = { 0.7f, 0.5f, -0.6f };
	GLfloat rightRBottomR[3] = { 0.7f, 0.5f, -0.58f };
	GLfloat rightRTopR[3] = { 0.7f, 0.54f, -0.58f };

	SquareRod(leftLTopR, leftLBottomR, leftRBottomR, leftRTopR, rightLTopR, rightLBottomR, rightRBottomR, rightRTopR, drawShadow);

	leftLTopR[1] = 0.62f;
	leftLBottomR[1] = 0.58f;
	leftRBottomR[1] = 0.58f;
	leftRTopR[1] = 0.62f;
	rightLTopR[1] = 0.62f;
	rightLBottomR[1] = 0.58f;
	rightRBottomR[1] = 0.58f;
	rightRTopR[1] = 0.62f;

	SquareRod(leftLTopR, leftLBottomR, leftRBottomR, leftRTopR, rightLTopR, rightLBottomR, rightRBottomR, rightRTopR, drawShadow);

	leftLTopR[1] = 0.7f;
	leftLBottomR[1] = 0.66f;
	leftRBottomR[1] = 0.66f;
	leftRTopR[1] = 0.7f;
	rightLTopR[1] = 0.7f;
	rightLBottomR[1] = 0.66f;
	rightRBottomR[1] = 0.66f;
	rightRTopR[1] = 0.7f;

	SquareRod(leftLTopR, leftLBottomR, leftRBottomR, leftRTopR, rightLTopR, rightLBottomR, rightRBottomR, rightRTopR, drawShadow);

	GLfloat leftLTopB[3] = { -0.7f, 0.54f, -0.58f };
	GLfloat leftLBottomB[3] = { -0.7f, 0.5f, -0.58f };
	GLfloat leftRBottomB[3] = { -0.7f, 0.5f, -0.6f };
	GLfloat leftRTopB[3] = { -0.7f, 0.54f, -0.6f };
	GLfloat rightLTopB[3] = { -0.7f, 0.54f, 0.6f };
	GLfloat rightLBottomB[3] = { -0.7f, 0.5f, 0.6f };
	GLfloat rightRBottomB[3] = { -0.7f, 0.5f, 0.58f };
	GLfloat rightRTopB[3] = { -0.7f, 0.54f, 0.58f };


	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[1] = 0.62f;
	leftLBottomB[1] = 0.58f;
	leftRBottomB[1] = 0.58f;
	leftRTopB[1] = 0.62f;
	rightLTopB[1] = 0.62f;
	rightLBottomB[1] = 0.58f;
	rightRBottomB[1] = 0.58f;
	rightRTopB[1] = 0.62f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[1] = 0.7f;
	leftLBottomB[1] = 0.66f;
	leftRBottomB[1] = 0.66f;
	leftRTopB[1] = 0.7f;
	rightLTopB[1] = 0.7f;
	rightLBottomB[1] = 0.66f;
	rightRBottomB[1] = 0.66f;
	rightRTopB[1] = 0.7f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = -0.68f;
	leftLTopB[1] = 0.7f;
	leftLTopB[2] = -0.58f;
	leftLBottomB[0] = -0.68f;
	leftLBottomB[1] = 0.7f;
	leftLBottomB[2] = -0.6f;
	leftRBottomB[0] = -0.7f;
	leftRBottomB[1] = 0.7f;
	leftRBottomB[2] = -0.6f;
	leftRTopB[0] = -0.7f;
	leftRTopB[1] = 0.7f;
	leftRTopB[2] = -0.58f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = 0.5f;
	rightLTopB[2] = -0.58f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = 0.5f;
	rightLBottomB[2] = -0.6f;
	rightRBottomB[0] = -0.68f;
	rightRBottomB[1] = 0.5f;
	rightRBottomB[2] = -0.6f;
	rightRTopB[0] = -0.68f;
	rightRTopB[1] = 0.5f;
	rightRTopB[2] = -0.6f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);


	leftLTopB[0] = 0.7f;
	leftLTopB[1] = 0.7f;
	leftLTopB[2] = -0.58f;
	leftLBottomB[0] = 0.7f;
	leftLBottomB[1] = 0.7f;
	leftLBottomB[2] = -0.6f;
	leftRBottomB[0] = 0.68f;
	leftRBottomB[1] = 0.7f;
	leftRBottomB[2] = -0.6f;
	leftRTopB[0] = 0.68f;
	leftRTopB[1] = 0.7f;
	leftRTopB[2] = -0.58f;

	rightLTopB[0] = 0.68f;
	rightLTopB[1] = 0.5f;
	rightLTopB[2] = -0.58f;
	rightLBottomB[0] = 0.68f;
	rightLBottomB[1] = 0.5f;
	rightLBottomB[2] = -0.6f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = 0.5f;
	rightRBottomB[2] = -0.6f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = 0.5f;
	rightRTopB[2] = -0.6f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//Central rest room for watch tower

	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.95f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.95f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.95f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.95f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.5f;
	rightLTopB[1] = 0.5f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = -0.5f;
	rightLBottomB[1] = 0.5f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.5f;
	rightRBottomB[1] = 0.5f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.5f;
	rightRTopB[1] = 0.5f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//roof
	leftLTopB[0] = 0.7f;
	leftLTopB[1] = 0.980f;
	leftLTopB[2] = 0.6f;
	leftLBottomB[0] = 0.7f;
	leftLBottomB[1] = 0.980f;
	leftLBottomB[2] = -0.6f;
	leftRBottomB[0] = -0.7f;
	leftRBottomB[1] = 0.980f;
	leftRBottomB[2] = -0.6f;
	leftRTopB[0] = -0.7f;
	leftRTopB[1] = 0.980f;
	leftRTopB[2] = 0.6f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = 0.95f;
	rightLTopB[2] = 0.6f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = 0.95f;
	rightLBottomB[2] = -0.6f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = 0.95f;
	rightRBottomB[2] = -0.6f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = 0.95f;
	rightRTopB[2] = 0.6f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	glBegin(GL_QUADS);

	glVertex3f(0.7f, 0.980f, 0.6f);
	glVertex3f(0.7f, 0.980f, -0.6f);
	glVertex3f(-0.7f, 0.980f, -0.6f);
	glVertex3f(-0.7f, 0.980f, 0.6f);

	glVertex3f(0.7f, 0.950f, 0.6f);
	glVertex3f(0.7f, 0.950f, -0.6f);
	glVertex3f(-0.7f, 0.950f, -0.6f);
	glVertex3f(-0.7f, 0.950f, 0.6f);

	glEnd();

	//Lower support
	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = 0.41f;
	leftRBottomB[0] = 0.45f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = 0.41f;
	leftRTopB[0] = 0.45f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.65f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = 0.65f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = 0.41f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = 0.41f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = -0.41f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = 0.45f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = 0.45f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = -0.41f;

	rightLTopB[0] = 0.65f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = -0.41f;
	rightLBottomB[0] = 0.65f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = -0.41f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = -0.45f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = -0.41f;
	leftLBottomB[0] = -0.45f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = -0.41f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = -0.41f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.65f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.65f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = -0.41f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = -0.45f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.45f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = 0.41f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = 0.41f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = 0.41f;
	rightRBottomB[0] = -0.65f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = 0.41f;
	rightRTopB[0] = -0.65f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//truss for lower support
	//A1
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A2
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C1
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C2
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B1
	leftLTopB[0] = 0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B2
	leftLTopB[0] = 0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D1
	leftLTopB[0] = -0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D2
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//cross truss bars

	//A0-A1
	leftLTopB[0] = -0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A1-A0
	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = 0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = -0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = -0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B0-B1
	leftLTopB[0] = 0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B1-B0
	leftLTopB[0] = 0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = 0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = 0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = 0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.45f;

	rightLTopB[0] = 0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = 0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.45f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//c0-c1
	leftLTopB[0] = -0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C1-C0
	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = 0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = 0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = -0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = -0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D0-D1
	leftLTopB[0] = -0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D1-D0
	leftLTopB[0] = -0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.45f;

	rightLTopB[0] = -0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = -0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.45f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A1-A2
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A2-A1
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B1-B2
	leftLTopB[0] = 0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B2-B1
	leftLTopB[0] = 0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C1-C2
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C2-C1
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D1-D2
	leftLTopB[0] = -0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);


	//D2-D1
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

}

void DrawHome_S5(bool drawShadow)
{

	//function declaration
	void SquareRod(GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, bool);

	glScalef(1.2f, 1.2f, 1.2f);
	glTranslatef(1.0f, 0.0f, -4.0f);


	glBindTexture(GL_TEXTURE_2D, texture_brick_S5);

	GLfloat leftLTop[3] = { 1.0f, 0.40f, 0.1f };
	GLfloat leftLBottom[3] = { 1.0f, 0.40f, -2.1f };
	GLfloat leftRBottom[3] = { -1.0f, 0.40f, -2.1f };
	GLfloat leftRTop[3] = { -1.0f, 0.40f, 0.1f };

	GLfloat rightLTop[3] = { -1.0f, -1.0f, 0.1f };
	GLfloat rightLBottom[3] = { -1.0f, -1.0f, -2.1f };
	GLfloat rightRBottom[3] = { 1.0f, -1.0f, -2.1f };
	GLfloat rightRTop[3] = { 1.0f, -1.0f, 0.1f };

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);


	leftLTop[0] = 0.5f;
	leftLTop[1] = 1.5f;
	leftLTop[2] = -0.3f;
	leftLBottom[0] = 0.50f;
	leftLBottom[1] = 1.5f;
	leftLBottom[2] = -2.1f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 1.5f;
	leftRBottom[2] = -2.1f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 1.5f;
	leftRTop[2] = -0.3f;

	rightLTop[0] = -1.0f;
	rightLTop[1] = 0.4f;
	rightLTop[2] = -0.3f;
	rightLBottom[0] = -1.0f;
	rightLBottom[1] = 0.4f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.5f;
	rightRBottom[1] = 0.4f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.5f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = -0.3f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = -0.25f;
	leftLTop[1] = 2.0f;
	leftLTop[2] = -2.3f;
	leftLBottom[0] = -0.250f;
	leftLBottom[1] = 2.0f;
	leftLBottom[2] = -2.3f;
	leftRBottom[0] = -1.20f;
	leftRBottom[1] = 1.3f;
	leftRBottom[2] = -2.3f;
	leftRTop[0] = -1.20f;
	leftRTop[1] = 1.4f;
	leftRTop[2] = -2.3f;

	rightLTop[0] = -1.20f;
	rightLTop[1] = 1.4f;
	rightLTop[2] = -0.2f;
	rightLBottom[0] = -1.20f;
	rightLBottom[1] = 1.3f;
	rightLBottom[2] = -0.2f;
	rightRBottom[0] = -0.25f;
	rightRBottom[1] = 2.0f;
	rightRBottom[2] = -0.2f;
	rightRTop[0] = -0.20f;
	rightRTop[1] = 2.0f;
	rightRTop[2] = -0.2f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.7f;
	leftLTop[1] = 1.40f;
	leftLTop[2] = -2.3f;
	leftLBottom[0] = 0.70f;
	leftLBottom[1] = 1.350f;
	leftLBottom[2] = -2.3f;
	leftRBottom[0] = -0.250f;
	leftRBottom[1] = 2.0f;
	leftRBottom[2] = -2.3f;
	leftRTop[0] = -0.250f;
	leftRTop[1] = 2.0f;
	leftRTop[2] = -2.3f;

	rightLTop[0] = -0.250f;
	rightLTop[1] = 2.0f;
	rightLTop[2] = -0.2f;
	rightLBottom[0] = -0.250f;
	rightLBottom[1] = 2.0f;
	rightLBottom[2] = -0.2f;
	rightRBottom[0] = 0.70f;
	rightRBottom[1] = 1.350f;
	rightRBottom[2] = -0.2f;
	rightRTop[0] = 0.7f;
	rightRTop[1] = 1.40f;
	rightRTop[2] = -0.2f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	//upper triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, 1.5f, -0.3f);
	glVertex3f(0.5f, 1.5f, -0.3f);
	glVertex3f(-0.25f, 2.0f, -0.3f);

	glVertex3f(-1.0f, 1.5f, -2.1f);
	glVertex3f(0.5f, 1.5f, -2.1f);
	glVertex3f(-0.25f, 2.0f, -2.1f);

	glEnd();

	//railing
	leftLTop[0] = -1.0f;
	leftLTop[1] = 0.50f;
	leftLTop[2] = 0.09f;
	leftLBottom[0] = -1.0f;
	leftLBottom[1] = 0.4750f;
	leftLBottom[2] = 0.09f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 0.4750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 0.50f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.50f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.4750f;
	rightLBottom[2] = 0.1f;
	rightRBottom[0] = 1.0f;
	rightRBottom[1] = 0.4750f;
	rightRBottom[2] = 0.09f;
	rightRTop[0] = 1.0f;
	rightRTop[1] = 0.5f;
	rightRTop[2] = 0.09f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = -1.0f;
	leftLTop[1] = 0.60f;
	leftLTop[2] = 0.09f;
	leftLBottom[0] = -1.0f;
	leftLBottom[1] = 0.5750f;
	leftLBottom[2] = 0.09f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 0.5750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 0.60f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.60f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.5750f;
	rightLBottom[2] = 0.1f;
	rightRBottom[0] = 1.0f;
	rightRBottom[1] = 0.5750f;
	rightRBottom[2] = 0.09f;
	rightRTop[0] = 1.0f;
	rightRTop[1] = 0.6f;
	rightRTop[2] = 0.09f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.990f;
	leftLTop[1] = 0.50f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = 0.990f;
	leftLBottom[1] = 0.4750f;
	leftLBottom[2] = 0.1f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.4750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.50f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.50f;
	rightLTop[2] = -2.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.4750f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.990f;
	rightRBottom[1] = 0.4750f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.990f;
	rightRTop[1] = 0.5f;
	rightRTop[2] = -2.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.990f;
	leftLTop[1] = 0.60f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = 0.990f;
	leftLBottom[1] = 0.5750f;
	leftLBottom[2] = 0.1f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.5750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.60f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.60f;
	rightLTop[2] = -2.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.5750f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.990f;
	rightRBottom[1] = 0.5750f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.990f;
	rightRTop[1] = 0.6f;
	rightRTop[2] = -2.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.90f;
	leftLTop[1] = 0.650f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = 0.90f;
	leftLBottom[1] = 0.65f;
	leftLBottom[2] = 0.08f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.650f;
	leftRBottom[2] = 0.08f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.650f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.40f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.70f;
	rightLBottom[2] = 0.08f;
	rightRBottom[0] = 0.90f;
	rightRBottom[1] = 0.70f;
	rightRBottom[2] = 0.08f;
	rightRTop[0] = 0.90f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = 0.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = -0.90f;
	leftLTop[1] = 0.650f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = -0.90f;
	leftLBottom[1] = 0.65f;
	leftLBottom[2] = 0.08f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 0.650f;
	leftRBottom[2] = 0.08f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 0.650f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = -1.0f;
	rightLTop[1] = 0.40f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = -1.0f;
	rightLBottom[1] = 0.70f;
	rightLBottom[2] = 0.08f;
	rightRBottom[0] = -0.90f;
	rightRBottom[1] = 0.70f;
	rightRBottom[2] = 0.08f;
	rightRTop[0] = -0.90f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = 0.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.90f;
	leftLTop[1] = 0.650f;
	leftLTop[2] = -2.08f;
	leftLBottom[0] = 0.90f;
	leftLBottom[1] = 0.65f;
	leftLBottom[2] = -2.1f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.650f;
	leftRBottom[2] = -2.1f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.650f;
	leftRTop[2] = -2.08f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.40f;
	rightLTop[2] = -2.08f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.70f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.90f;
	rightRBottom[1] = 0.70f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.90f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = -2.08f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	//Door

	glBindTexture(GL_TEXTURE_2D, texture_door_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3f, 0.1f, 0.12f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, -1.0f, 0.12f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.3f, -1.0f, 0.12f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.3f, 0.1f, 0.12f);



	//window
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.01f, 0.071f, -0.25f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.01f, -0.70f, -0.25f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.01f, -0.70f, -1.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.01f, 0.071f, -1.5f);


	glEnd();


}


void SquareRod(GLfloat* leftLTop, GLfloat* leftLBottom, GLfloat* leftRBottom, GLfloat* leftRTop, GLfloat* rightLTop, GLfloat* rightLBottoom, GLfloat* rightRBottom, GLfloat* rightRTop, bool shadowFlag)
{
	if (shadowFlag)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);


		glVertex3fv(leftRTop);
		glVertex3fv(leftRBottom);
		glVertex3fv(rightLBottoom);
		glVertex3fv(rightLTop);


		//2

		glVertex3fv(leftRTop);
		glVertex3fv(rightLTop);
		glVertex3fv(rightRTop);
		glVertex3fv(leftLTop);


		//3
		glVertex3fv(rightRTop);
		glVertex3fv(rightRBottom);
		glVertex3fv(leftLBottom);
		glVertex3fv(leftLTop);

		//4
		glVertex3fv(rightLBottoom);
		glVertex3fv(leftRBottom);
		glVertex3fv(leftLBottom);
		glVertex3fv(rightRBottom);
		glEnd();
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(leftRTop);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(leftRBottom);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(rightLBottoom);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(rightLTop);


		//2

		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(leftRTop);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(rightLTop);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(rightRTop);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(leftLTop);


		//3
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(rightRTop);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(rightRBottom);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(leftLBottom);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(leftLTop);

		//4
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(rightLBottoom);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(leftRBottom);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(leftLBottom);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(rightRBottom);
		glEnd();
	}

}


void DrawTreeBranch_S5(node *tree, GLfloat angle, bool shadow)
{
	if (tree != NULL && tree->left != NULL && tree->right != NULL)
	{
		glPushMatrix();
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, tree->length * -0.9f);
		DrawTreeBranch_S5(tree->left, 30.0f, shadow);
		DrawTreeBranch_S5(tree->right, -30.0f, shadow);

		quadric_SSD = gluNewQuadric();

		if (!shadow)
		{
			glBindTexture(GL_TEXTURE_2D, stem_texture_S5);
			gluQuadricTexture(quadric_SSD, true);
		}
		else
			glColor3f(0.0f, 0.0f, 0.0f);

		gluCylinder(quadric_SSD, tree->small_radius, tree->large_radius, tree->length, 10, 10);
		glPopMatrix();


		glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, tree->length * -0.9f);
		DrawTreeBranch_S5(tree->left, 40.0f, shadow);
		DrawTreeBranch_S5(tree->right, -40.0f, shadow);

		quadric_SSD = gluNewQuadric();

		if (!shadow)
		{
			glBindTexture(GL_TEXTURE_2D, stem_texture_S5);
			gluQuadricTexture(quadric_SSD, true);
		}
		else
			glColor3f(0.0f, 0.0f, 0.0f);

		gluCylinder(quadric_SSD, tree->small_radius, tree->large_radius, tree->length, 10, 10);
		glPopMatrix();
	}

}

void DrawTreeBranch__S5(node *tree, GLfloat angle)
{
	if (tree != NULL && tree->left != NULL && tree->right != NULL)
	{
		glPushMatrix();
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, tree->length * -0.9f);
		DrawTreeBranch__S5(tree->left, 30.0f);
		DrawTreeBranch__S5(tree->right, -30.0f);

		quadric_SSD = gluNewQuadric();

		glBindTexture(GL_TEXTURE_2D, stem_texture_S5);
		gluQuadricTexture(quadric_SSD, true);
		
		gluCylinder(quadric_SSD, tree->small_radius, tree->large_radius, tree->length, 10, 10);
		glPopMatrix();


		glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, tree->length * -0.9f);
		DrawTreeBranch__S5(tree->left, 40.0f);
		DrawTreeBranch__S5(tree->right, -40.0f);

		quadric_SSD = gluNewQuadric();

		glBindTexture(GL_TEXTURE_2D, stem_texture_S5);
		gluQuadricTexture(quadric_SSD, true);
		

		gluCylinder(quadric_SSD, tree->small_radius, tree->large_radius, tree->length, 10, 10);
		glPopMatrix();
	}

}

node* InsertNode_S5(node *root, GLfloat small_radius, GLfloat large_radius, GLfloat length, GLint level, GLint numberOfBranches)
{
	if (level < numberOfBranches)
	{
		//root = NULL;
		root = (node*)malloc(sizeof(node));

		if (root == NULL)
		{
			fprintf_s(gbFile, "memory allocation for node is unsuccessful, exiting\n");
			DestroyWindow(ghwnd);
		}

		root->large_radius = large_radius;
		root->small_radius = small_radius;
		root->length = length;

		//fprintf_s(gbFile_SSD, "%f\n", root->large_radius);

		root->left = NULL;
		root->right = NULL;

		root->left = InsertNode_S5(root->left, small_radius * 0.5f, large_radius * 0.5f, length * 0.7f, level + 1, numberOfBranches);
		root->right = InsertNode_S5(root->right, small_radius * 0.5f, large_radius * 0.5f, length * 0.7f, level + 1, numberOfBranches);

		return root;
	}

	return root;
}


void DrawGround_S5(GLint sceneNumber)
{
	//scene 4 calculations
	static GLfloat leftX = -55.0f;
	static GLfloat rightX = 55.0f;
	static GLfloat upperY = 45.0f;
	static GLfloat backwardZ = -54.5f;
	static GLfloat frontZ = 5.5f;

	//glTranslatef(0.0f, 0.0f, -3.0f);
	//glScalef(0.7f, 0.7f, 0.7f);
	glColor3f(0.0f, 1.0f, 0.0f);

	//glBindTexture(GL_TEXTURE_2D, texture_grass);

	if (endScene_S5)
		frontZ = 30.0f;
	/*if (!endScene)
	{*/

	//glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(leftX, -3.0f, backwardZ);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(leftX, -3.0f, frontZ);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(rightX, -3.0f, frontZ);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(rightX, -3.0f, backwardZ);

		glEnd();
	//}
	
	

	if (sceneNumber == 4)
	{

		if (endScene_S5)
		{
			glBindTexture(GL_TEXTURE_2D, mahadev_tex_S5);
			glDisable(GL_FOG);
		}
			

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-55.5f, 30.0f, 20.4f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-55.5f, -1.0f, 20.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-55.5f, -1.0f, -26.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-55.5f, 30.0f, -26.5f);

		glEnd();

		/*glPushMatrix();

		glTranslatef(xFurther, yFurther, zFurther);


		fprintf_s(gbFile_SSD, "xFurther=%f, yFurther=%f, zFurther=%f\n", xFurther, yFurther, zFurther);

		if (endScene_S5)
		{
			glBindTexture(GL_TEXTURE_2D, trishul_tex_S5);
			glDisable(GL_FOG);
		}


		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-55.5f, 30.0f, 20.4f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-55.5f, -1.0f, 20.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-55.5f, -1.0f, -26.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-55.5f, 30.0f, -26.5f);

		glEnd();

		glPopMatrix();
		*/
	}
	
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glBindTexture(GL_TEXTURE_2D, texture_sky);

	
	/*if (!endScene)
	{*/

	/*GLfloat leftX = -55.0f;
	GLfloat rightX = 55.0f;
	GLfloat upperY = 45.0f;
	GLfloat backwardZ = -54.5f*/

	if (sceneNumber == 4)
	{
		leftX = -200.0f;
		rightX = 200.0f;
		backwardZ = -250.0f;
		upperY = 200.0f;
	}

	glEnable(GL_FOG);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(leftX, -3.3f, backwardZ);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(rightX, -3.3f, backwardZ);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(rightX, upperY, backwardZ);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(leftX, upperY, backwardZ);

		glEnd();

	//}

		/*if (startDarkness && sceneNumber == 4)
		{
			leftX -= 0.2f;
			rightX += 0.2f;
			upperY += 0.2f;
			backwardZ -= 0.2f;

			if (backwardZ <= -2520.0f)
				startDarkness = false;
		}*/
	
}


void Fly_S5(GLint *counter, bool fall, GLfloat flappingFly, GLfloat speed)
{
	//scene1 flapping 0.5, yTrans 0.0004, forward movement -0.001, headPos 0.04
	flapping_S5 = flappingFly;

	if (!fall)
	{
		if (birdYTrans_S5 <= 1.0f)
		{
			birdYTrans_S5 += 0.004f;
			birdForwardMovement_S5 -= 0.00041f * speed;
		}
			
		else
			birdForwardMovement_S5 -= 0.001f * speed;
	}

	if (headPos_S5 < 30.0f)
		headPos_S5 += 0.04f * speed;


	if (*counter == 100000)
		*counter = 0;

	if (leftWalkAngle_S5 < 0.0f)
		leftWalkAngle_S5 += 0.1f;

	if (leftWalkAngle_S5 > 0.0f)
		leftWalkAngle_S5 -= 0.1f;

	if (rightWalkAngle_S5 < 0.0f)
		rightWalkAngle_S5 += 0.1f;

	if (rightWalkAngle_S5 > 0.0f)
		rightWalkAngle_S5 -= 0.1f;

	/*static bool flappingFlag = true;
	static bool isWalk = false;
	static bool fall = false;
	static bool getUp = false;

	void WingsFlapping(GLint*, bool*, bool*, bool*, bool*);

	if (flappingFlag)
	{
		WingsFlapping(counter, &flappingFlag, &isWalk, &fall, &getUp);
		birdForwardMovement -= 0.0002f;
	}
	else
	{
		flapping = 0.6f;
		birdForwardMovement -= 0.0006f;
	}*/

}

void Walk_S5(bool walk, GLfloat speed)
{
	static bool leftLegWalk = true;
	static bool rightLegWalk = false;
	static bool rightLegReturn = true;
	static bool leftLegReturn = false;

	if (walk)
	{
		if (leftLegWalk)
		{
			if (leftWalkAngle_S5 < 30.0f)
			{
				leftWalkAngle_S5 += 0.051f * speed;
			}
			else
			{
				leftLegReturn = true;
				leftLegWalk = false;
			}
		}
		if (rightLegWalk)
		{
			if (rightWalkAngle_S5 < 30.0f)
			{
				rightWalkAngle_S5 += 0.051f * speed;
			}
			else
			{
				rightLegReturn = true;
				rightLegWalk = false;
			}
		}
		if (leftLegReturn)
		{
			if (leftWalkAngle_S5 > -30.0f)
			{
				leftWalkAngle_S5 -= 0.051f * speed;
			}
			else
			{
				leftLegReturn = false;
				leftLegWalk = true;
			}
		}
		if (rightLegReturn)
		{
			if (rightWalkAngle_S5 > -30.0f)
			{
				rightWalkAngle_S5 -= 0.051f * speed;
			}
			else
			{
				rightLegReturn = false;
				rightLegWalk = true;
			}
		}

		birdForwardMovement_S5 -= 0.0001f * speed;
	}

}

/*if the wing angle is required to be lowered while walking pass isWalk as true*/
void BirdModel_S5(bool isWalk)
{

	//function declaration
	void DrawCylinder(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, CYLINDER_CODS);
	void Leg_S5(GLfloat);


	CYLINDER_CODS cods = { 0.0f, 0.0f, 0.0f, 15.0f };
	GLfloat radius;
	GLfloat zValue;
	GLUquadric *quadric = NULL;
	
	static bool upMovement = false;
	static bool downMovement = true;
	static bool lowerWingUpMovement = false;
	static bool lowerWingDownMovement = false;
	static bool lowerWingReturn = false;

	static bool sideupMovement = false;
	static bool sidedownMovement = true;
	static bool sidelowerWingUpMovement = false;
	static bool sidelowerWingDownMovement = false;
	static bool sidelowerWingReturn = false;
	static bool flappingFlag = true;
	static GLfloat checkFirstOccur = 1.0f;
	GLfloat x1, x2, x3, x4, z1, z2, z3, z4;

	if (isWalk)
	{
		lowerWingsFlap_S5 = 30.0f;
		sideLowerWingFlap_S5 = -30.0f;
	}

	//fprintf_s(gbFile, "WINGSaNGLEa=%f, wingsbngle=%f\n", wingsFlap, sideWingFlap);
	//basic body
	DrawCylinder(0.1f, 0.1f, 0.30f, 0.0f, 0.0f, cods);

	//legs
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glRotatef(-headPos_S5, 1.0f, 0.0f, 0.0f);
	//glRotatef(leftWalkAngle, 1.0f, 0.0f, 0.0f);
	Leg_S5(leftWalkAngle_S5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.0f, 0.0f);
	glRotatef(-headPos_S5, 1.0f, 0.0f, 0.0f);
	//glRotatef(rightWalkAngle, 1.0f, 0.0f, 0.0f);
	Leg_S5(rightWalkAngle_S5);
	glPopMatrix();

	fprintf_s(gbFile, "headZ==%f headY==%f\n", headPos_S5, headPosY_S5);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.341000f);
	glTranslatef(0.0f, 0.070000f, 0.0f);
	glScalef(1.0f, 1.0f, 1.2f);
	quadric = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluSphere(quadric, 0.11, 10, 10);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.06f, 0.08f, -0.05f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.06f, -0.03f, 0.0f);

	glVertex3f(-0.06f, 0.08f, -0.05f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(-0.06f, -0.03f, 0.0f);

	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.0f, -0.068f, -0.17f);
	glVertex3f(0.0f, -0.03f, -0.14f);

	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.0f, -0.068f, -0.17f);
	glVertex3f(0.0f, -0.03f, -0.14f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.06f, 0.08f, -0.05f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(-0.06f, 0.08f, -0.05f);
	glEnd();


	glPopMatrix();

	//fprintf_s(gbFile, "headZ==%f headY==%f\n", headPos, headPosY);

	glPushMatrix();//1

	glTranslatef(0.0f, 0.0f, 0.4f);
	glPushMatrix();//2
	glScalef(1.0f, 1.0f, 3.0f);
	quadric = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluSphere(quadric, 0.2f, 20, 20);

	//tail

	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.05f, 0.091f, 0.172f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1f, 0.2f, 0.34f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.34f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.05f, 0.091f, 0.171f);


	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.12f, 0.091f, 0.162f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.33f, 0.2f, 0.34f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.13f, 0.2f, 0.34f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.07f, 0.091f, 0.161f);


	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.12f, 0.091f, 0.162f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.13f, 0.2f, 0.34f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.33f, 0.2f, 0.34f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.07f, 0.091f, 0.161f);

	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.12f, 0.05f, 0.162f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.34f, 0.21f, 0.34f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.39f, 0.21f, 0.34f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.07f, 0.05f, 0.161f);

	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.12f, 0.05f, 0.162f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.46f, 0.22f, 0.34f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.34f, 0.22f, 0.34f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.07f, 0.05f, 0.161f);

	
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.06f, 0.06f, 0.162f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.14f, 0.24f, 0.34f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.14f, 0.24f, 0.34f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.07f, 0.06f, 0.161f);

	glEnd();

	GLfloat y1_SSD = -0.1;
	GLfloat y2_SSD = 0.1f;

	for (int i = 0; i < 10; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.1f, y1_SSD, 0.142f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.34f, y2_SSD, 0.3f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.34f, y2_SSD, 0.3f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.1f, y1_SSD, 0.141f);
		glEnd();

		y1_SSD += 0.2 / 10;
		y2_SSD += 0.2 / 30;
	}



	glPopMatrix();//2-

	glPushMatrix();//2

	glTranslatef(0.0f, -0.05f, -0.14f);
	glScalef(1.0f, 1.0f, 1.6f);
	quadric = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);

	gluSphere(quadric, 0.15f, 20, 20);

	glPopMatrix();//2-

	glPopMatrix();//1-

	//wings
	glPushMatrix();//1

	//wings flapping mechanism
	if (downMovement)
	{
		wingsFlap_S5 += flapping_S5;
		if (wingsFlap_S5 >= 10) {
			downMovement = false;
			upMovement = true;
			lowerWingDownMovement = true;
			lowerWingReturn = false;
		}

	}
	if (upMovement && lowerWingReturn)
	{
		wingsFlap_S5 -= flapping_S5;
		if (wingsFlap_S5 <= -60.0f) {
			upMovement = false;
			downMovement = true;
		}
	}

	if (flappingFlag)
		glRotatef(wingsFlap_S5, 0.0f, 0.0f, 1.0f);
	else
	{
		flapping_S5 = 0.0f;
		if (wingsFlap_S5 <= 5.0f || wingsFlap_S5 >= 3.0f)
		{
			glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
		}
	}
	
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.43f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.53f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	//lower wing
	glPushMatrix();//2

	if (lowerWingDownMovement)
	{
		lowerWingsFlap_S5 += flapping_S5;
		if (lowerWingsFlap_S5 >= 50.0f)
		{
			lowerWingDownMovement = false;
			lowerWingUpMovement = true;
		}
	}
	if (lowerWingUpMovement)
	{
		lowerWingsFlap_S5 -= flapping_S5;
		if (lowerWingsFlap_S5 <= 0.0f)
		{
			lowerWingUpMovement = false;
			lowerWingReturn = true;
		}
	}

	glTranslatef(-0.6f, 0.0f, 0.0f);
	glRotatef(lowerWingsFlap_S5, 0.0f, 0.0f, 1.0f);


	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.9f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, 0.0f, 0.43f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.43f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	//feathers

	x1 = -0.8f; x2 = -0.98f; x3 = -0.93f; x4 = -0.73f;
	z1 = 0.04f; z2 = 0.05f; z3 = 0.06f; z4 = 0.05f;

	while (x1 <= -0.260f)
	{
		glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x1, 0.0f, z1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x2, 0.0f, z2);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x3, 0.0f, z3);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x4, 0.0f, z4);

		x1 += 0.035f;
		x2 += 0.035f;
		x3 += 0.035f;
		x4 += 0.035f;

		z1 += 0.024f;
		z2 += 0.024f;
		z3 += 0.024f;
		z4 += 0.024f;
		glEnd();
	}

	glPopMatrix();//2-

	glPopMatrix();//1-
	//***************************************************************************************************
	glPushMatrix();//1

	if (checkFirstOccur == 1.0f)
		Sleep(10);

	checkFirstOccur += 0.001f;
	//wings flapping mechanism
	if (downMovement)
	{
		sideWingFlap_S5 -= flapping_S5;
		if (sideWingFlap_S5 <= -10)
		{
			sidedownMovement = false;
			sidelowerWingDownMovement = true;
			sidelowerWingReturn = false;
			sideupMovement = true;
		}

	}
	if (upMovement && lowerWingReturn)
	{
		sideWingFlap_S5 += flapping_S5;
		if (sideWingFlap_S5 >= 60.0f)
		{
			sidedownMovement = true;
			sideupMovement = false;
		}
	}

	if (flappingFlag)
		glRotatef(sideWingFlap_S5, 0.0f, 0.0f, 1.0f);
	else
	{
		flapping_S5 = 0.0f;
		glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
	}


	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.43f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.53f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	//lower wing
	glPushMatrix();//2

	if (lowerWingDownMovement)
	{
		sideLowerWingFlap_S5 -= flapping_S5;
		if (sideLowerWingFlap_S5 <= -50.0f)
		{
			sidelowerWingDownMovement = false;
			sidelowerWingUpMovement = true;
		}
	}
	if (lowerWingUpMovement)
	{
		sideLowerWingFlap_S5 += flapping_S5;
		if (lowerWingsFlap_S5 >= 0.0f)
		{
			sidelowerWingUpMovement = false;
			sidelowerWingReturn = true;
		}
	}

	glTranslatef(0.6f, 0.0f, 0.0f);
	glRotatef(sideLowerWingFlap_S5, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.9f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.3f, 0.0f, 0.43f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.43f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	x1 = 0.8f; x2 = 0.98f; x3 = 0.93f; x4 = 0.73f;
	z1 = 0.04f; z2 = 0.05f; z3 = 0.06f; z4 = 0.05f;

	while (x1 >= 0.260f)
	{
		glBindTexture(GL_TEXTURE_2D, texture_feather_S5);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x1, 0.0f, z1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x2, 0.0f, z2);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x3, 0.0f, z3);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x4, 0.0f, z4);

		x1 -= 0.035f;
		x2 -= 0.035f;
		x3 -= 0.035f;
		x4 -= 0.035f;

		z1 += 0.024f;
		z2 += 0.024f;
		z3 += 0.024f;
		z4 += 0.024f;
		glEnd();
	}

	glPopMatrix();//2-

	glPopMatrix();//1-

}

void Leg_S5(GLfloat flyAngle)
{
	GLUquadric *quadric = NULL;

	//1
	glPushMatrix();//1
	glTranslatef(0.0f, 0.0f, 0.155000f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluCylinder(quadric, 0.07, 0.07, 0.42, 20, 20);

	glPushMatrix();//2
	//2
	glTranslatef(0.0f, 0.02f, 0.372000);
	glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluCylinder(quadric, 0.07f, 0.07, 0.3, 20, 20);
	glPushMatrix();//3
	//3
	glTranslatef(0.0f, 0.0f, 0.279000);
	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluCylinder(quadric, 0.07f, 0.03, 0.2, 20, 20);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.186000);
	glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluCylinder(quadric, 0.02f, 0.0041, 0.15, 20, 20);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.186000);
	glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluCylinder(quadric, 0.02f, 0.0041, 0.15, 20, 20);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.100000, 0.124000);
	glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
	//glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture_feather_S5);

	gluQuadricTexture(quadric, true);
	gluCylinder(quadric, 0.0038f, 0.02, 0.15, 20, 20);
	glPopMatrix();

	glPopMatrix();//-3
	glPopMatrix();//-2
	glPopMatrix();//-1
}

void WingsFlapping_S5(GLint *counter, bool* flappingFlag, bool *walk, bool* fall, bool *getUp, GLfloat upWardSpeed)
{
	//function declaration
	void Fall_S5(bool*);

	//static GLint COUNTER = 0;
	static bool fallCount = 0;
	//static bool getUp = false;

	*walk = false;

	if (birdYTrans_S5 >= -0.51f && birdYTrans_S5 <= -0.49f)
		*walk = true;

	if (*counter > 5500 && *counter < 6500)//5500 10000
	{
		birdYTrans_S5 += 0.001f * upWardSpeed;
		if (headPos_S5 < 30.0f)
			headPos_S5 += 0.04f * upWardSpeed;
		*walk = false;
		leftWalkAngle_S5 = 0.0f;
		rightWalkAngle_S5 = 0.0f;
	}

	fprintf_s(gbFile, "counter=%d, yTrans=%f\n", *counter, birdYTrans_S5);

	if (*counter == 6500) //10000
	{
		if (*fall)
		{
			fallCount = true;
		}
		*flappingFlag = false;
		flapping_S5 = 0.05f;
		*counter = 0;
	}
	if (*counter == 5500)//5500
	{
		flapping_S5 = 0.8f * upWardSpeed;
	}
	if (*counter == 100000)
		*flappingFlag = false;

	//fprintf_s(gbFile, "flapping==%f\n", flapping);

	if (birdYTrans_S5 >= -0.5f)
	{
		if (*fall == true && fallCount == true)
		{
			birdYTrans_S5 -= 0.0041f * upWardSpeed;
			//Fall(&fall);
			//headPos = 0.0f;
			if (birdYTrans_S5 >= -0.51f && birdYTrans_S5 <= -0.49f)
			{
				*fall = false;
				fallCount = false;
				Fall_S5(fall);
				*getUp = true;
			}
		}
		else if (*getUp == false)
		{
			birdYTrans_S5 -= 0.0007f * upWardSpeed;
			if (headPos_S5 > 0.0f)
				headPos_S5 -= 0.02f * upWardSpeed;
		}
		else
		{
			if (headPos_S5 > 0.0f)
			{
				headPos_S5 -= 0.03f * upWardSpeed;
				birdYTrans_S5 += 0.00005f * upWardSpeed;
			}

			else
				*getUp = false;
		}


		//if (fall && fallCount == 1 && birdYTrans <= -0.5f)
			//Fall(&fall);

	}

	//COUNTER++;
	//fprintf_s(gbFile, "counter==%d\n", COUNTER);
}


void Fall_S5(bool *fall)
{
	GLdouble fallCount = 0.0;
	while (fallCount < 100000.0)
	{
		fallCount += 0.0005;
	}
}

/*For this function we must pass two radius and a length, however instead of length we can pass the angle so that
the linear equation could evalute the height accordingly.*/
void DrawCylinder(GLfloat radiusBottom, GLfloat radiusTop, GLfloat length, GLfloat initialZValue, GLfloat angle, CYLINDER_CODS cylinderCods)
{
	GLfloat grad = 10;
	GLfloat alpha = 0.0f;
	GLfloat x, y, z = 0;
	GLfloat z1 = 0.0f;
	GLfloat radius = 0.0f;
	GLfloat radiusTemp;
	GLfloat radiusGradient;
	GLfloat max_dip_height;
	GLfloat dip_gradient;

	//linear equation to create inclined cyliinder
	//calculating the height which is gradient
	if (cylinderCods.depping_angle != 0)
		max_dip_height = length * sin(cylinderCods.depping_angle * GL_PI / 180);


	//a linear equation need to be created to get the varying values of radius
	if (radiusTop < radiusBottom)
	{
		radiusTemp = radiusTop;
		radiusGradient = radiusBottom - radiusTop;
	}
	else {
		radiusTemp = radiusBottom;
		radiusGradient = radiusTop - radiusBottom;
	}



	while (z1 <= (length))
	{
		if (radiusBottom != radiusTop)
		{
			if (angle != 0.0f)
			{
				radius = radiusTemp + z1 * tan(angle * GL_PI / 180);
			}
			else
			{
				angle = atan((radiusGradient) / (4.0f * length));
				radius = radiusTemp + z1 * tan(angle * GL_PI / 180);
			}
		}
		else
			radius = radiusBottom;

		if (cylinderCods.depping_angle != 0)
			dip_gradient = z1 * sin(cylinderCods.depping_angle * GL_PI / 180);

		for (alpha = 0.0f; alpha <= 2.0f * GL_PI; alpha = alpha + ((2.0f * GL_PI) / 10))
		{
			//glBindTexture(GL_TEXTURE_2D, texture_brick);
			glBegin(GL_QUADS);

			x = radius * sin(alpha) + cylinderCods.x1;
			y = radius * cos(alpha) + dip_gradient;
			z = z1 * -1.0f - initialZValue;

			glVertex3f(x, y, z);

			x = radius * sin(alpha + ((2.0f * GL_PI) / 10)) + cylinderCods.x1;
			y = radius * cos(alpha + ((2.0f * GL_PI) / 10)) + dip_gradient;
			z = z1 * -1.0f - initialZValue;

			glVertex3f(x, y, z);

			x = radius * sin(alpha + ((2.0f * GL_PI) / 10)) + cylinderCods.x1;
			y = radius * cos(alpha + ((2.0f * GL_PI) / 10)) + dip_gradient;
			z = (z1 + (length / grad)) * -1.0f - initialZValue;

			glVertex3f(x, y, z);

			x = radius * sin(alpha) + cylinderCods.x1;
			y = radius * cos(alpha) + dip_gradient;
			z = (z1 + (length / grad))* -1.0f - initialZValue;

			glVertex3f(x, y, z);

			glEnd();
		}

		z1 = z1 + (length / grad);
	}

}

void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3)
{
	// Get two vectors... do the cross product
	M3DVector3f v1, v2;

	// V1 = p3 - p1
	v1[0] = p3[0] - p1[0];
	v1[1] = p3[1] - p1[1];
	v1[2] = p3[2] - p1[2];

	// V2 = P2 - p1
	v2[0] = p2[0] - p1[0];
	v2[1] = p2[1] - p1[1];
	v2[2] = p2[2] - p1[2];

	// Unit normal to plane - Not sure which is the best way here
	m3dCrossProduct(planeEq, v1, v2);
	m3dNormalizeVector(planeEq);
	// Back substitute to get D
	planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}

void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos)
{
	// These just make the code below easier to read. They will be 
	// removed by the optimizer.	
	float a = planeEq[0];
	float b = planeEq[1];
	float c = planeEq[2];
	float d = planeEq[3];

	float dx = -vLightPos[0];
	float dy = -vLightPos[1];
	float dz = -vLightPos[2];

	// Now build the projection matrix
	proj[0] = b * dy + c * dz;
	proj[1] = -a * dy;
	proj[2] = -a * dz;
	proj[3] = 0.0;

	proj[4] = -b * dx;
	proj[5] = a * dx + c * dz;
	proj[6] = -b * dz;
	proj[7] = 0.0;

	proj[8] = -c * dx;
	proj[9] = -c * dy;
	proj[10] = a * dx + b * dy;
	proj[11] = 0.0;

	proj[12] = -d * dx;
	proj[13] = -d * dy;
	proj[14] = -d * dz;
	proj[15] = a * dx + b * dy + c * dz;
	// Shadow matrix ready
}

bool LoadTexture(GLuint *texture, TCHAR imageResource[])
{
	HBITMAP hBitmap;
	BITMAP bmp;
	bool bStatus = false;

	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResource, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hBitmap)
	{
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		glBindTexture(GL_TEXTURE_2D, 0);
		DeleteObject(hBitmap);
		bStatus = true;

	}
	return bStatus;
}


//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//code for scene2

void Display_2(bool *Scene_2_Completed)
{
	void PushPopRecur(GLint, GLfloat);
	void DrawTree(bool, GLint);
	void DrawTree_(bool, GLint);
	void HumanAnimation(void);
	void BirdModel(bool);
	void WingsFlapping(GLint*, bool*, bool*, bool*, bool*);
	void Walk(bool);
	void Fly(GLint*);

	//variable declaration
	static bool blackOut = false;
	//flapping of wings
	static GLint counter = 0;

	//variable declaration
	static bool flappingFlag = true;
	static bool walk = false;
	static GLfloat travel = 0.0f;
	static bool fall = true;
	static bool getUp = false;
	static bool showBird = false;
	static bool birdFromHuman = false;

	static bool stopScene = true;
	static bool blackOutComplete = false;
	static GLfloat birdYMovement_S2 = 0.80f;

	//colors
	static GLfloat terrainR1 = 1.0f;
	static GLfloat terrainG1 = 0.7f;
	static GLfloat sunRG = 1.0f;
	static GLfloat humanColor = 0.3f;
	static GLfloat general = 0.1f;

	//bird movement in texture scene
	static GLfloat birdBackwardMovement_S3 = 3.0f;
	static GLfloat birdForwardMovement_S3 = 20.0f;

	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();

	
	gluLookAt(cameraX_scene2, cameraY_scene2, cameraZ_scene2, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	if (!scene1Completed)
	{
		glPushMatrix();

		glBegin(GL_QUADS);
		glColor3f(terrainR1, terrainG1, 0.0f);
		glVertex3f(-7.0f, -0.5f, -4.0f);
		glVertex3f(6.0f, -0.5f, -4.0f);
		glColor3f(general, general, general);
		glVertex3f(6.0f, 4.0f, -4.0f);
		glVertex3f(-7.0f, 4.0f, -4.0f);
		glEnd();

		glPopMatrix();


		//bird**********************
		if (showBird)
		{
			glPushMatrix();

			//glTranslatef(0.0f, 0.0f, -5.0f);
			glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, birdYMovement, 0.0f);
			glTranslatef(0.0f, 0.0f, birdBackwardMovementBird);
			glTranslatef(birdXMovement, 0.0f, 0.0f);
			glScalef(0.15f, 0.15f, 0.15f);
			//glRotatef(yAngle, 0.0f, 1.0f, 0.0f);


			birdBackwardMovementBird -= 0.005f;
			birdXMovement += 0.051f;
			//WingsFlapping(&counter, &flappingFlag, &walk, &fall, &getUp);
			Fly(&counter);

			fprintf_s(gbFile_SSD, "BackWardMovement=%f, yMovement=%f, xMovement=%f\n", birdBackwardMovementBird, birdYMovement, birdXMovement);
			glRotatef(25.0f, 1.0f, 0.0f, 0.0f);

			BirdModel(walk);

			//Walk(walk);


			counter++;

			if (counter == 100000)
				counter = 0;

			glPopMatrix();

		}

		//sun*********************
		glPushMatrix();
		glColor3f(sunRG, sunRG, 0.0f);
		glTranslatef(-0.2f, 0.1f, -2.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.2, 20, 20);

		//fprintf_s(gbFile_SSD, "%f==x%f==y\n", xTrans, yTrans);
		glPopMatrix();

		glColor3f(general, general, general);

		//Big tree 2*********************
		glPushMatrix();
		glTranslatef(-1.20f, -0.30f, -0.40f);
		glScalef(0.5f, 0.5f, 0.5f);
		//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//PushPopRecur(0, 0.0f);

		//glColor3f(0.0f, 1.0f, 0.0f);
		DrawTree(true, 7);
		glPopMatrix();




		if (!showBird)
		{
			//tree 4*************
			glPushMatrix();
			glTranslatef(2.1f, -0.340f, -1.40f);
			glScalef(0.051f, 0.051f, 0.051f);
			DrawTree_(true, 4);
			glPopMatrix();

			//tree 3*************
			glPushMatrix();
			glTranslatef(1.80f, -0.3f, -1.0f);
			glScalef(0.2f, 0.2f, 0.2f);
			DrawTree(true, 7);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(2.1f, -0.30f, -0.40f);
			glScalef(0.1f, 0.1f, 0.1f);
			DrawTree_(true, 4);
			glPopMatrix();


			//tree 1*************
			glPushMatrix();
			glTranslatef(-3.4f, -0.3f, -1.70f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.1f, 0.1f, 0.1f);
			DrawTree(true, 7);
			glPopMatrix();

			//Human ***************
			glPushMatrix();
			glScalef(0.2f, 0.2f, 0.2f);
			glTranslatef(xTrans_scene2, yTrans_scene2, zTrans_scene2);
			glRotatef(yRot_scene2, 0.0f, 1.0f, 0.0f);
			glColor3f(humanColor, humanColor, humanColor);
			HumanAnimation();

			//fprintf_s(gbFile_SSD, "rot=%f\n", yRot);
			glPopMatrix();

		}

		if (!sit)
		{
			if (xTrans_scene2 < 6.3f)
			{
				yRot_scene2 = 270.0f;
				xTrans_scene2 -= 0.08f;
				zTrans_scene2 += 0.04f;
			}
			else
			{
				xTrans_scene2 -= 0.082f;
				zTrans_scene2 += 0.082f;
			}

			if (xTrans_scene2 < 4.13f && cameraZ_scene2 > 1.20f)
			{
				cameraZ_scene2 -= 0.051f;
				cameraX_scene2 += 0.0088f;

			}
			if (xTrans_scene2 < -0.13f && xTrans_scene2 > -5.5f)//***********++
			{
				//stopScene = true;
				showBird = true;
			}
			if (cameraZ_scene2 <= 1.2f && xTrans_scene2 <= -7.5f)//***************
			{
				blackOut = true;
				//showBird = false;
			}

			if (blackOut)
			{
				general -= 0.01f;//**********++
				sunRG -= 0.01f;
				terrainR1 -= 0.01f;
				terrainG1 -= 0.01f;
				humanColor = 0.0f;
			}

			if (terrainG1 <= 0.0f && sunRG <= 0.0f)
			{
				blackOutComplete = true;
				blackOut = false;

			}
		}

		if (blackOutComplete)
		{
			if (general <= 0.1f)
				general += 0.001f;//**********++

			if (general <= 1.0f)
				sunRG += 0.01f;

			if (terrainR1 <= 1.0f)
				terrainR1 += 0.01f;

			if (terrainG1 <= 0.7f)
				terrainG1 += 0.007f;

			if (humanColor <= 0.3f)
				humanColor += 0.003f;

			if (terrainR1 >= 0.4f)
				birdFromHuman = true;

			showBird = false;
			sit = true;


			cameraZ_scene2 = 3.0f;
			cameraY_scene2 = -0.1f;
			cameraX_scene2 = 0.0f;
			xTrans_scene2 = -0.255f;
			zTrans_scene2 = 6.0f;
			yRot_scene2 = 2.0f;

		}

		
	}
	else
	{
		glPushMatrix();

		//glTranslatef(0.0f, 0.0f, -5.0f);
		if (birdBackwardMovement_S3 >= -15.0f)
		{
			glTranslatef(0.0f, birdYMovement_S2, 0.0f);
			glTranslatef(0.0f, 0.0f, birdBackwardMovement_S3);
			birdBackwardMovement_S3 -= 0.003f;

		}
		else
		{
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, birdForwardMovement_S3);
			birdForwardMovement_S3 -= 0.005f;
		}

		//glTranslatef(birdXMovement, 0.0f, 0.0f);
		glScalef(0.3f, 0.3f, 0.3f);
		//glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

		birdXMovement += 0.051f;
		//WingsFlapping(&counter, &flappingFlag, &walk, &fall, &getUp);
		Fly(&counter);

		fprintf_s(gbFile_SSD, "BackWardMovement=%f\n", birdBackwardMovement_S3);
		glRotatef(25.0f, 1.0f, 0.0f, 0.0f);

		BirdModel(walk);

		//Walk(walk);


		counter++;

		if (counter == 100000)
			counter = 0;


		glPopMatrix();

		//ground***************************
		glPushMatrix();

		if (birdBackwardMovement_S3 >= -15.0f)
		{
			glBindTexture(GL_TEXTURE_2D, nature_texture);
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-40.0f, 26.0f, -35.0f);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-40.0f, -14.0f, -35.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(40.0f, -14.0f, -35.0f);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(40.0f, 26.0f, -35.0f);
			glEnd();

		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, nature1_texture);
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-30.0f, 22.0f, -35.0f);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-30.0f, -12.0f, -35.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(30.0f, -12.0f, -35.0f);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(30.0f, 22.0f, -35.0f);
			glEnd();

		}


		glPopMatrix();


		
	}

	fprintf_s(gbFile_SSD, "terrainR1=%f\n", terrainR1);
	if (blackOutComplete && terrainR1 >= 1.0f)
	{
		scene1Completed = true;
		fprintf_s(gbFile_SSD, "Successfully inside\n");
	}

	fprintf_s(gbFile_SSD, "!!!!!!!!!!forward=%f\n", birdForwardMovement_S3);

	if (birdForwardMovement_S3 <= -0.8f)
	{
		fprintf_s(gbFile_SSD, "successs!!!!!!!!!!!!!!!!!!\n");
		*Scene_2_Completed = true;
	}

	
}

void DrawTree(bool shadow, GLint numberOfBranches)
{
	void DrawTreeBranch(node *, GLfloat);
	node* InsertNode(node*, GLfloat, GLfloat, GLfloat, GLint, GLint);
	void Uninitalize_tree(node*);

	static node* root = NULL;
	static node *root_val = NULL;
	static node *branch = NULL;
	static node *branch_val = NULL;
	static GLint root_counter = 1;
	static GLint branch_counter = 1;

	if (unitialize && root_val != NULL)
	{
		Uninitalize_tree(root_val->left);
		Uninitalize_tree(root_val->right);
		free(root_val);
		root_val = NULL;
	}
	else
	{
		if (root_counter == 1)
			root_val = InsertNode(root, 0.0410f * 2.0f, 0.0810f * 2.0f, 0.8f * 2.0f, 0, numberOfBranches);

		root_counter++;
		if (root_counter == 100000)
		{
			root_counter = 2;
		}

		if (branch_counter == 1)
			branch_val = InsertNode(branch, 0.04f, 0.08f, 0.5f, 0, numberOfBranches);

		branch_counter++;
		if (branch_counter == 100000)
		{
			branch_counter = 2;
		}

		/*quadric_SSD = gluNewQuadric();
		gluCylinder(quadric_SSD, 0.12f, 0.16f, 1.2f, 20, 20);
		quadric_SSD = gluNewQuadric();*/

		glTranslatef(0.0f, -1.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(xAngle_scene2, 0.0f, 0.0f, 1.0f);

		DrawTreeBranch(root_val, 0.0f);

	}


	
	/*glPushMatrix();
	glTranslatef(0.0f, xTrans, 0.0f);

	fprintf_s(gbFile_SSD, "%f==xTrans\n", xTrans);

	glTranslatef(0.0f, 0.0f, yTrans);

	fprintf_s(gbFile_SSD, "%f==yTrans\n", yTrans);

	//glTranslatef(zTrans, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	DrawTreeBranch(branch_val, 0.0f);
	glPopMatrix();*/
}

void DrawTree_(bool shadow, GLint numberOfBranches)
{
	void DrawTreeBranch(node *, GLfloat);
	node* InsertNode(node*, GLfloat, GLfloat, GLfloat, GLint, GLint);
	void Uninitalize_tree(node*);

	static node* root = NULL;
	static node *root_val = NULL;
	static node *branch = NULL;
	static node *branch_val = NULL;
	static GLint root_counter = 1;
	static GLint branch_counter = 1;

	if (unitialize && root_val != NULL)
	{
		Uninitalize_tree(root_val->left);
		Uninitalize_tree(root_val->right);
		free(root_val);
		root_val = NULL;
	}
	else
	{
		if (root_counter == 1)
			root_val = InsertNode(root, 0.0410f * 2.0f, 0.0810f * 2.0f, 0.8f * 2.0f, 0, numberOfBranches);

		root_counter++;
		if (root_counter == 100000)
		{
			root_counter = 2;
		}

		if (branch_counter == 1)
			branch_val = InsertNode(branch, 0.04f, 0.08f, 0.5f, 0, numberOfBranches);

		branch_counter++;
		if (branch_counter == 100000)
		{
			branch_counter = 2;
		}

		/*quadric_SSD = gluNewQuadric();
		gluCylinder(quadric_SSD, 0.12f, 0.16f, 1.2f, 20, 20);
		quadric_SSD = gluNewQuadric();*/

		glTranslatef(0.0f, -1.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(xAngle_scene2, 0.0f, 0.0f, 1.0f);

		DrawTreeBranch(root_val, 0.0f);

	}

	
	/*glPushMatrix();
	glTranslatef(0.0f, xTrans, 0.0f);

	fprintf_s(gbFile_SSD, "%f==xTrans\n", xTrans);

	glTranslatef(0.0f, 0.0f, yTrans);

	fprintf_s(gbFile_SSD, "%f==yTrans\n", yTrans);

	//glTranslatef(zTrans, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	DrawTreeBranch(branch_val, 0.0f);
	glPopMatrix();*/
}


void DrawTreeBranch(node *tree, GLfloat angle)
{
	if (tree != NULL && tree->left != NULL && tree->right != NULL)
	{
		glPushMatrix();
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, tree->length * -0.9f);
		DrawTreeBranch(tree->left, 30.0f);
		DrawTreeBranch(tree->right, -30.0f);
		quadric_SSD = gluNewQuadric();
		gluCylinder(quadric_SSD, tree->small_radius, tree->large_radius, tree->length, 10, 10);
		glPopMatrix();


		glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, tree->length * -0.9f);
		DrawTreeBranch(tree->left, 40.0f);
		DrawTreeBranch(tree->right, -40.0f);
		quadric_SSD = gluNewQuadric();
		gluCylinder(quadric_SSD, tree->small_radius, tree->large_radius, tree->length, 10, 10);
		glPopMatrix();
	}

}

node* InsertNode(node *root, GLfloat small_radius, GLfloat large_radius, GLfloat length, GLint level, GLint numberOfBranches)
{
	if (level < numberOfBranches)
	{
		//root = NULL;
		root = (node*)malloc(sizeof(node));

		if (root == NULL)
		{
			//fprintf_s(gbFile_SSD, "memory allocation for node is unsuccessful, exiting\n");
			DestroyWindow(ghwnd);
		}

		root->large_radius = large_radius;
		root->small_radius = small_radius;
		root->length = length;

		//fprintf_s(gbFile_SSD, "%f\n", root->large_radius);
		root->left = NULL;
		root->right = NULL;

		root->left = InsertNode(root->left, small_radius * 0.5f, large_radius * 0.5f, length * 0.7f, level + 1, numberOfBranches);
		root->right = InsertNode(root->right, small_radius * 0.5f, large_radius * 0.5f, length * 0.7f, level + 1, numberOfBranches);

		return root;
	}
	return root;
}


void HumanAnimation(void)
{

	//function declaration
	void WalkHuman(bool);
	void DrawSphere(GLfloat, GLfloat, GLfloat, GLfloat);

	glRotatef(yTrans_scene2, 0.0f, 1.0f, 0.0f);

	//if (!sit)
		//WalkHuman(true);

	//************************************************************************************
	//head
	glPushMatrix();
	glScalef(1.0f, 1.4f, 1.0f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluSphere(quadric_SSD, 0.1f, 20, 20);
	glPopMatrix();

	//*************************************************************************************
	//neck
	glPushMatrix();
	glTranslatef(0.0f, 0.62f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.028f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluCylinder(quadric_SSD, 0.06f, 0.06f, 0.09f, 10, 10);
	glPopMatrix();

	//**************************************************************************************
	//body
	//neck to main body slant height
	glPushMatrix();
	glTranslatef(0.0f, 0.55f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.02f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.4f, 0.80f, 1.0f);
	quadric_SSD = gluNewQuadric();
	gluCylinder(quadric_SSD, 0.06f, 0.14f, 0.051f, 20, 20);

	//main body
	glPushMatrix();
	glScalef(1.0f, 1.21f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.06f);
	quadric_SSD = gluNewQuadric();
	gluCylinder(quadric_SSD, 0.125f, 0.1f, 0.4f, 20, 20);

	glPopMatrix();
	glPopMatrix();

	//***************************************************************************************
	//hands
	//left hand**************************
	glPushMatrix();
	glTranslatef(-0.19f, 0.0f, 0.0f); //-0.19
	glTranslatef(0.0f, 0.49f, 0.0f);

	if (sit)
	{
		glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.19f, 0.0f);
		glScalef(1.0f, 4.7f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.042f, 20, 20);

	}
	else
	{
		glRotatef(leftWalkAngleHandHuman, 1.0f, 0.0f, 0.0f);//0.37
		glTranslatef(0.0f, -0.13f, 0.0f);
		glScalef(1.0f, 3.8f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.038f, 20, 20);
	}


	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//lower arm
	glPushMatrix();
	glTranslatef(0.0f, -0.05f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluSphere(quadric_SSD, 0.032f, 20, 20);
	glPopMatrix();

	glPopMatrix();

	//right hand*******************
	glPushMatrix();
	glTranslatef(0.19f, 0.0f, 0.0f); //-0.19
	glTranslatef(0.0f, 0.49f, 0.0f);
	if (sit)
	{
		glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.19f, 0.0f);
		glScalef(1.0f, 4.7f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.042f, 20, 20);

	}
	else
	{
		glRotatef(rightWalkAngleHandHuman, 1.0f, 0.0f, 0.0f);//0.37
		glTranslatef(0.0f, -0.13f, 0.0f);
		glScalef(1.0f, 3.8f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.038f, 20, 20);
	}



	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//lower arm
	glPushMatrix();
	glTranslatef(0.0f, -0.05f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluSphere(quadric_SSD, 0.032f, 20, 20);
	glPopMatrix();

	glPopMatrix();

	//***************************************************************************
	//legs
	//left leg**********************
	glPushMatrix();

	if (sit)
	{
		glTranslatef(-0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.03f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25, 4.3f);
		DrawSphere(0.072f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		glTranslatef(-0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.08f, 0.0f);
		glRotatef(leftWalkAngleHuman, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25f, 4.3f);
		DrawSphere(0.072f, 0.0f, 0.0f, 0.0f);
	}

	//lower leg

	if (sit)
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 0.061f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(4.30f, 1.250f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.056f, 20, 20);
	}
	else
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.046f, 20, 20);
	}



	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//*******************************
	//foot
	if (!sit)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.032800f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(1.0f, 2.50f, 1.0f);
		glTranslatef(0.0f, 0.022f, 0.02f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.04f, 10, 10);
		glPopMatrix();
	}


	glPopMatrix();

	glPopMatrix();

	//right leg**********************
	glPushMatrix();

	if (sit)
	{
		glTranslatef(0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.03f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25, 4.3f);
		DrawSphere(0.072f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		glTranslatef(0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.08f, 0.0f);
		glRotatef(rightWalkAngleHuman, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25f, 4.3f);
		DrawSphere(0.072f, 0.0f, 0.0f, 0.0f);
	}




	//lower leg

	if (sit)
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 0.061f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(4.30f, 1.250f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.056f, 20, 20);
	}
	else
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.046f, 20, 20);
	}

	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//*******************************
	//foot

	if (!sit)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.032800f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(1.0f, 2.50f, 1.0f);
		glTranslatef(0.0f, 0.022f, 0.02f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.04f, 10, 10);
		glPopMatrix();
	}

	glPopMatrix();

	glPopMatrix();



}

void DrawSphere(GLfloat radius, GLfloat X1, GLfloat Y1, GLfloat Z1)
{
	GLfloat x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLfloat a, b;
	GLfloat grade = 40;

	for (a = 0.0f; a <= GL_PI / 1.90f; a += (GL_PI / grade))
	{
		glBegin(GL_POLYGON);

		for (b = 0.0f; b <= 2.0f * GL_PI; b += (GL_PI / grade))
		{
			x1 = radius * cos(b) * sin(a);
			y1 = radius * sin(b) * sin(a);
			z1 = radius * cos(a);

			glVertex3f(x1 + X1, y1 + Y1, z1 + Z1);

			x2 = radius * cos(b + (GL_PI / grade)) * sin(a);
			y2 = radius * sin(b + (GL_PI / grade)) * sin(a);
			z2 = radius * cos(a);

			glVertex3f(x2 + X1, y2 + Y1, z2 + Z1);

			x3 = radius * cos(b) * sin(a + (GL_PI / grade));
			y3 = radius * sin(b) * sin(a + (GL_PI / grade));
			z3 = radius * cos(a + (GL_PI / grade));

			glVertex3f(x3 + X1, y3 + Y1, z3 + Z1);

			x4 = radius * cos(b + (GL_PI / grade)) * sin(a + (GL_PI / grade));
			y4 = radius * sin(b + (GL_PI / grade)) * sin(a + (GL_PI / grade));
			z4 = radius * cos(a + (GL_PI / grade));

			glVertex3f(x4 + X1, y4 + Y1, z4 + Z1);


			//
		}

		glEnd();
	}
}

void WalkHuman(bool walk)
{
	static bool leftLegWalk = true;
	static bool rightLegWalk = false;
	static bool rightLegReturn = true;
	static bool leftLegReturn = false;
	static GLfloat speed = 100.0f;

	if (walk)
	{
		if (leftLegWalk)
		{
			if (leftWalkAngleHandHuman > -40.0f)
			{
				leftWalkAngleHandHuman -= (0.102f * speed);
			}

			if (leftWalkAngleHuman < 20.0f)
			{
				leftWalkAngleHuman += (0.051f * speed);
			}
			else
			{
				leftLegReturn = true;
				leftLegWalk = false;
			}


		}
		if (rightLegWalk)
		{
			if (rightWalkAngleHandHuman > -40.0f)
			{
				rightWalkAngleHandHuman -= (0.102f * speed);
			}

			if (rightWalkAngleHuman < 20.0f)
			{
				rightWalkAngleHuman += (0.051f * speed);
			}
			else
			{
				rightLegReturn = true;
				rightLegWalk = false;
			}

		}
		if (leftLegReturn)
		{
			if (leftWalkAngleHandHuman < 40.0f)
			{
				leftWalkAngleHandHuman += (0.102f * speed);
			}

			if (leftWalkAngleHuman > -20.0f)
			{
				leftWalkAngleHuman -= (0.051f * speed);
			}
			else
			{
				leftLegReturn = false;
				leftLegWalk = true;
			}
		}
		if (rightLegReturn)
		{
			if (rightWalkAngleHandHuman < 40.0f)
			{
				rightWalkAngleHandHuman += (0.102f * speed);
			}

			if (rightWalkAngleHuman > -20.0f)
			{
				rightWalkAngleHuman -= (0.051f * speed);
			}
			else
			{
				rightLegReturn = false;
				rightLegWalk = true;
			}
		}

	}

}

void Fly(GLint *counter)
{
	if (!scene1Completed)
		flappingBird = 32.8f;
	else
		flappingBird = 1.0f;

	birdYTransBird += 0.04f;

	if (headPosBird < 30.0f)
		headPosBird += 1.4f;

	if (*counter == 100000)
		*counter = 0;
	/*static bool flappingFlag = true;
	static bool isWalk = false;
	static bool fall = false;
	static bool getUp = false;

	void WingsFlapping(GLint*, bool*, bool*, bool*, bool*);

	if (flappingFlag)
	{
		WingsFlapping(counter, &flappingFlag, &isWalk, &fall, &getUp);
		birdForwardMovement -= 0.0002f;
	}
	else
	{
		flapping = 0.6f;
		birdForwardMovement -= 0.0006f;
	}*/

}

void Walk(bool walk)
{
	static bool leftLegWalk = true;
	static bool rightLegWalk = false;
	static bool rightLegReturn = true;
	static bool leftLegReturn = false;

	if (walk)
	{
		if (leftLegWalk)
		{
			if (leftWalkAngleBird < 30.0f)
			{
				leftWalkAngleBird += 0.051f;
			}
			else
			{
				leftLegReturn = true;
				leftLegWalk = false;
			}
		}
		if (rightLegWalk)
		{
			if (rightWalkAngleBird < 30.0f)
			{
				rightWalkAngleBird += 0.051f;
			}
			else
			{
				rightLegReturn = true;
				rightLegWalk = false;
			}
		}
		if (leftLegReturn)
		{
			if (leftWalkAngleBird > -30.0f)
			{
				leftWalkAngleBird -= 0.051f;
			}
			else
			{
				leftLegReturn = false;
				leftLegWalk = true;
			}
		}
		if (rightLegReturn)
		{
			if (rightWalkAngleBird > -30.0f)
			{
				rightWalkAngleBird -= 0.051f;
			}
			else
			{
				rightLegReturn = false;
				rightLegWalk = true;
			}
		}

		birdForwardMovementBird -= 0.0001f;
	}

}

/*if the wing angle is required to be lowered while walking pass isWalk as true*/
void BirdModel(bool isWalk)
{

	//function declaration
	void DrawCylinder(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, CYLINDER_CODS);
	void Leg(GLfloat);


	CYLINDER_CODS cods = { 0.0f, 0.0f, 0.0f, 15.0f };
	GLfloat radius;
	GLfloat zValue;
	GLUquadric *quadric = NULL;
	static GLfloat wingsFlap = 0.0f;
	static GLfloat sideWingFlap = 0.0f;
	static GLfloat lowerWingsFlap = 0.0f;
	static GLfloat sideLowerWingFlap = 0.0f;
	static bool upMovement = false;
	static bool downMovement = true;
	static bool lowerWingUpMovement = false;
	static bool lowerWingDownMovement = false;
	static bool lowerWingReturn = false;

	static bool sideupMovement = false;
	static bool sidedownMovement = true;
	static bool sidelowerWingUpMovement = false;
	static bool sidelowerWingDownMovement = false;
	static bool sidelowerWingReturn = false;
	static bool flappingFlag = true;
	static GLfloat checkFirstOccur = 1.0f;
	GLfloat x1, x2, x3, x4, z1, z2, z3, z4;

	if (isWalk)
	{
		lowerWingsFlap = 30.0f;
		sideLowerWingFlap = -30.0f;
	}

	//basic body
	DrawCylinder(0.1f, 0.1f, 0.30f, 0.0f, 0.0f, cods);

	//legs
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glRotatef(-headPosBird, 1.0f, 0.0f, 0.0f);
	//glRotatef(leftWalkAngle, 1.0f, 0.0f, 0.0f);
	Leg(leftWalkAngleBird);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.0f, 0.0f);
	glRotatef(-headPosBird, 1.0f, 0.0f, 0.0f);
	//glRotatef(rightWalkAngle, 1.0f, 0.0f, 0.0f);
	Leg(rightWalkAngleBird);
	glPopMatrix();

	//fprintf_s(gbFile_SSD, "headZ==%f headY==%f\n", headPosBird, headPosYBird);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.341000f);
	glTranslatef(0.0f, 0.070000f, 0.0f);
	glScalef(1.0f, 1.0f, 1.2f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.11, 10, 10);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.06f, 0.08f, -0.05f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.06f, -0.03f, 0.0f);

	glVertex3f(-0.06f, 0.08f, -0.05f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(-0.06f, -0.03f, 0.0f);

	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.0f, -0.068f, -0.17f);
	glVertex3f(0.0f, -0.03f, -0.14f);

	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.0f, -0.068f, -0.17f);
	glVertex3f(0.0f, -0.03f, -0.14f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.06f, 0.08f, -0.05f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(0.0f, -0.04f, -0.17f);
	glVertex3f(-0.06f, 0.08f, -0.05f);
	glEnd();


	glPopMatrix();

	//fprintf_s(gbFile, "headZ==%f headY==%f\n", headPos, headPosY);

	glPushMatrix();//1

	glTranslatef(0.0f, 0.0f, 0.4f);
	glPushMatrix();//2
	glScalef(1.0f, 1.0f, 3.0f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.2f, 20, 20);

	//tail
	glBegin(GL_QUADS);
	glVertex3f(-0.05f, 0.091f, 0.172f);
	glVertex3f(-0.1f, 0.2f, 0.34f);
	glVertex3f(0.1f, 0.2f, 0.34f);
	glVertex3f(0.05f, 0.091f, 0.171f);

	glVertex3f(-0.12f, 0.091f, 0.162f);
	glVertex3f(-0.33f, 0.2f, 0.34f);
	glVertex3f(-0.13f, 0.2f, 0.34f);
	glVertex3f(-0.07f, 0.091f, 0.161f);

	glVertex3f(0.12f, 0.091f, 0.162f);
	glVertex3f(0.13f, 0.2f, 0.34f);
	glVertex3f(0.33f, 0.2f, 0.34f);
	glVertex3f(0.07f, 0.091f, 0.161f);

	glVertex3f(0.12f, 0.05f, 0.162f);
	glVertex3f(0.34f, 0.21f, 0.34f);
	glVertex3f(0.39f, 0.21f, 0.34f);
	glVertex3f(0.07f, 0.05f, 0.161f);

	glVertex3f(-0.12f, 0.05f, 0.162f);
	glVertex3f(-0.46f, 0.22f, 0.34f);
	glVertex3f(-0.34f, 0.22f, 0.34f);
	glVertex3f(-0.07f, 0.05f, 0.161f);

	glVertex3f(-0.06f, 0.06f, 0.162f);
	glVertex3f(-0.14f, 0.24f, 0.34f);
	glVertex3f(0.14f, 0.24f, 0.34f);
	glVertex3f(0.07f, 0.06f, 0.161f);

	glEnd();

	GLfloat y1_SSD = -0.1;
	GLfloat y2_SSD = 0.1f;

	for (int i = 0; i < 10; i++)
	{
		glBegin(GL_QUADS);
		glVertex3f(-0.1f, y1_SSD, 0.142f);
		glVertex3f(-0.34f, y2_SSD, 0.3f);
		glVertex3f(0.34f, y2_SSD, 0.3f);
		glVertex3f(0.1f, y1_SSD, 0.141f);
		glEnd();

		y1_SSD += 0.2 / 10;
		y2_SSD += 0.2 / 30;
	}



	glPopMatrix();//2-

	glPushMatrix();//2

	glTranslatef(0.0f, -0.05f, -0.14f);
	glScalef(1.0f, 1.0f, 1.6f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.15f, 20, 20);

	glPopMatrix();//2-

	glPopMatrix();//1-

	//wings
	glPushMatrix();//1

	//wings flapping mechanism
	if (downMovement)
	{
		wingsFlap += flappingBird;
		if (wingsFlap >= 10) {
			downMovement = false;
			upMovement = true;
			lowerWingDownMovement = true;
			lowerWingReturn = false;
		}

	}
	if (upMovement && lowerWingReturn)
	{
		wingsFlap -= flappingBird;
		if (wingsFlap <= -60.0f) {
			upMovement = false;
			downMovement = true;
		}
	}

	if (flappingFlag)
		glRotatef(wingsFlap, 0.0f, 0.0f, 1.0f);
	else
	{
		flappingBird = 0.0f;
		if (wingsFlap <= 5.0f || wingsFlap >= 3.0f)
		{
			glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	glBegin(GL_QUADS);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.43f);
	glVertex3f(0.0f, 0.0f, 0.53f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	//lower wing
	glPushMatrix();//2

	if (lowerWingDownMovement)
	{
		lowerWingsFlap += flappingBird;
		if (lowerWingsFlap >= 50.0f)
		{
			lowerWingDownMovement = false;
			lowerWingUpMovement = true;
		}
	}
	if (lowerWingUpMovement)
	{
		lowerWingsFlap -= flappingBird;
		if (lowerWingsFlap <= 0.0f)
		{
			lowerWingUpMovement = false;
			lowerWingReturn = true;
		}
	}

	glTranslatef(-0.6f, 0.0f, 0.0f);
	glRotatef(lowerWingsFlap, 0.0f, 0.0f, 1.0f);


	glBegin(GL_QUADS);
	glVertex3f(-0.9f, 0.0f, 0.0f);
	glVertex3f(-0.3f, 0.0f, 0.43f);
	glVertex3f(0.0f, 0.0f, 0.43f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	//feathers

	x1 = -0.8f; x2 = -0.98f; x3 = -0.93f; x4 = -0.73f;
	z1 = 0.04f; z2 = 0.05f; z3 = 0.06f; z4 = 0.05f;

	while (x1 <= -0.260f)
	{
		glBegin(GL_QUADS);
		glVertex3f(x1, 0.0f, z1);
		glVertex3f(x2, 0.0f, z2);
		glVertex3f(x3, 0.0f, z3);
		glVertex3f(x4, 0.0f, z4);

		x1 += 0.035f;
		x2 += 0.035f;
		x3 += 0.035f;
		x4 += 0.035f;

		z1 += 0.024f;
		z2 += 0.024f;
		z3 += 0.024f;
		z4 += 0.024f;
		glEnd();
	}

	glPopMatrix();//2-

	glPopMatrix();//1-
	//***************************************************************************************************
	glPushMatrix();//1

	if (checkFirstOccur == 1.0f)
		Sleep(10);

	checkFirstOccur += 0.001f;
	//wings flapping mechanism
	if (downMovement)
	{
		sideWingFlap -= flappingBird;
		if (sideWingFlap <= -10)
		{
			sidedownMovement = false;
			sidelowerWingDownMovement = true;
			sidelowerWingReturn = false;
			sideupMovement = true;
		}

	}
	if (upMovement && lowerWingReturn)
	{
		sideWingFlap += flappingBird;
		if (sideWingFlap >= 60.0f)
		{
			sidedownMovement = true;
			sideupMovement = false;
		}
	}

	if (flappingFlag)
		glRotatef(sideWingFlap, 0.0f, 0.0f, 1.0f);
	else
	{
		flappingBird = 0.0f;
		glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
	}


	glBegin(GL_QUADS);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.43f);
	glVertex3f(0.0f, 0.0f, 0.53f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	//lower wing
	glPushMatrix();//2

	if (lowerWingDownMovement)
	{
		sideLowerWingFlap -= flappingBird;
		if (sideLowerWingFlap <= -50.0f)
		{
			sidelowerWingDownMovement = false;
			sidelowerWingUpMovement = true;
		}
	}
	if (lowerWingUpMovement)
	{
		sideLowerWingFlap += flappingBird;
		if (lowerWingsFlap >= 0.0f)
		{
			sidelowerWingUpMovement = false;
			sidelowerWingReturn = true;
		}
	}

	glTranslatef(0.6f, 0.0f, 0.0f);
	glRotatef(sideLowerWingFlap, 0.0f, 0.0f, 1.0f);


	glBegin(GL_QUADS);
	glVertex3f(0.9f, 0.0f, 0.0f);
	glVertex3f(0.3f, 0.0f, 0.43f);
	glVertex3f(0.0f, 0.0f, 0.43f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	x1 = 0.8f; x2 = 0.98f; x3 = 0.93f; x4 = 0.73f;
	z1 = 0.04f; z2 = 0.05f; z3 = 0.06f; z4 = 0.05f;

	while (x1 >= 0.260f)
	{
		glBegin(GL_QUADS);
		glVertex3f(x1, 0.0f, z1);
		glVertex3f(x2, 0.0f, z2);
		glVertex3f(x3, 0.0f, z3);
		glVertex3f(x4, 0.0f, z4);

		x1 -= 0.035f;
		x2 -= 0.035f;
		x3 -= 0.035f;
		x4 -= 0.035f;

		z1 += 0.024f;
		z2 += 0.024f;
		z3 += 0.024f;
		z4 += 0.024f;
		glEnd();
	}

	glPopMatrix();//2-

	glPopMatrix();//1-

}

void Leg(GLfloat flyAngle)
{
	GLUquadric *quadric = NULL;

	//1
	glPushMatrix();//1
	glTranslatef(0.0f, 0.0f, 0.155000f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.07, 0.07, 0.42, 20, 20);

	glPushMatrix();//2
	//2
	glTranslatef(0.0f, 0.02f, 0.372000);
	glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.07f, 0.07, 0.3, 20, 20);
	glPushMatrix();//3
	//3
	glTranslatef(0.0f, 0.0f, 0.279000);
	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.07f, 0.03, 0.2, 20, 20);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.186000);
	glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.02f, 0.0041, 0.15, 20, 20);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.186000);
	glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.02f, 0.0041, 0.15, 20, 20);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.100000, 0.124000);
	glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
	//glRotatef(flyAngle, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.0038f, 0.02, 0.15, 20, 20);
	glPopMatrix();

	glPopMatrix();//-3
	glPopMatrix();//-2
	glPopMatrix();//-1
}

void WingsFlapping(GLint *counter, bool* flappingFlag, bool *walk, bool* fall, bool *getUp)
{
	//function declaration
	void Fall(bool*);

	//static GLint COUNTER = 0;
	static bool fallCount = 0;
	//static bool getUp = false;

	*walk = false;

	if (birdYTransBird >= -0.51f && birdYTransBird <= -0.49f)
		*walk = true;

	if (*counter > 5500 && *counter < 10000)
	{
		birdYTransBird += 0.001f;
		if (headPosBird < 30.0f)
			headPosBird += 0.04f;
		*walk = false;
		leftWalkAngleBird = 0.0f;
		rightWalkAngleBird = 0.0f;
	}

	if (*counter == 10000)
	{
		if (*fall)
		{
			fallCount = true;
		}
		*flappingFlag = false;
		flappingBird = 0.05f;
		*counter = 0;
	}
	if (*counter == 5500)
	{
		flappingBird = 0.8f;
	}
	if (*counter == 100000)
		*flappingFlag = false;

	//fprintf_s(gbFile, "flapping==%f\n", flapping);

	if (birdYTransBird >= -0.5f)
	{
		if (*fall == true && fallCount == true)
		{
			birdYTransBird -= 0.0041f;
			//Fall(&fall);
			//headPos = 0.0f;
			if (birdYTransBird >= -0.51f && birdYTransBird <= -0.49f)
			{
				*fall = false;
				fallCount = false;
				Fall(fall);
				*getUp = true;
			}
		}
		else if (*getUp == false)
		{
			birdYTransBird -= 0.0007f;
			if (headPosBird > 0.0f)
				headPosBird -= 0.02f;
		}
		else
		{
			if (headPosBird > 0.0f)
			{
				headPosBird -= 0.03f;
				birdYTransBird += 0.00005f;
			}

			else
				*getUp = false;
		}


		//if (fall && fallCount == 1 && birdYTrans <= -0.5f)
			//Fall(&fall);

	}

	//COUNTER++;
	//fprintf_s(gbFile, "counter==%d\n", COUNTER);
}

void Fall(bool *fall)
{
	GLdouble fallCount = 0.0;
	while (fallCount < 100000.0)
	{
		fallCount += 0.0005;
	}
}

//////////////////////////////////////////////////////////////////
//scene1 functions*******************************************************
void Display_1(bool *scene_1_completed)
{

	//variable declaration
	GLfloat lightPos_scene1[] = { lightXPos_scene1, lightYPos_scene1, lightZPos_scene1, 1.0f };
	//GLfloat specLight_scene1[] = { 0.40f, 0.40f, 0.40f, 0.4f };
	//GLfloat diffuseLight_scene1[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	//GLfloat specRef_scene1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientLight_scene1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientLight1_scene1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat baseWidth_scene1 = 0.9f;
	M3DVector3f vNormal_scene1;
	M3DVector3f vPoints_scene1[3];
	M3DVector3f shadowPoints_scene1[3] = { {-2.0f * 0.7f, -1.30f * 0.7f, -2.0f * 0.7f},
								  {-2.0f * 0.7f, -1.30f * 0.7f, 2.0f * 0.7f},
								  {2.0f * 0.7f, -1.30f * 0.7f, 2.0f * 0.7f} };

	M3DVector3f shadowPointsHome_scene1[3] = { {-2.0f * 1.2f, -1.00f * 1.2f, -2.0f * 1.2f},
								  {-2.0f * 1.2f, -1.0f * 1.2f, 2.0f * 1.2f},
								  {2.0f * 1.2f, -1.0f * 1.2f, 2.0f * 1.2f} };

	M3DVector4f vPlaneEquation_scene1;
	M3DMatrix44f vShadowMatrix_scene1;
	M3DVector4f vPlaneEquationHome_scene1;
	M3DMatrix44f vShadowMatrixHome_scene1;

	//variables for human animation
	static bool soulWalkStart_scene1 = false;
	static GLfloat time_count = 7.0f;
	static bool start_going_back_camera = false;
	static GLfloat cabfY = 0.0f;
	
	//function declaration
	void DrawGround_scene1(void);
	void DrawTower(bool);
	void DrawHome(bool);
	void HumanAnimation_scene1(GLfloat, bool);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glFrontFace(GL_CCW);


	glLightModelfv(GL_AMBIENT, ambientLight_scene1);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos_scene1);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight_scene1);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, specRef_scene1);
	//glMateriali(GL_FRONT, GL_SHININESS, 128);

	//shadow calculations
	m3dGetPlaneEquation(vPlaneEquation_scene1, shadowPoints_scene1[0], shadowPoints_scene1[1], shadowPoints_scene1[2]);

	m3dMakePlanarShadowMatrix(vShadowMatrix_scene1, vPlaneEquation_scene1, lightPos_scene1);

	m3dGetPlaneEquation(vPlaneEquationHome_scene1, shadowPointsHome_scene1[0], shadowPointsHome_scene1[1], shadowPointsHome_scene1[2]);

	m3dMakePlanarShadowMatrix(vShadowMatrixHome_scene1, vPlaneEquationHome_scene1, lightPos_scene1);


	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -3.0f);
	gluLookAt(xRotate_scene1, yRotate_scene1, zRotate_scene1, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//zRotate=0.009887, xRotate=-0.000294, yRotate=0.001398
	//here we are coding for consequential changes aftter bird falling
	if (camerAfterBirdFall)
	{
		glRotatef(cabfY, 0.0f, 0.0f, 1.0f);

		if (time_count <= -14.2f)
			cabfY = 20.0f;

		if (time_count <= -14.22f)
			cabfY = -20.0f;

		if (time_count <= -14.24f)
			cabfY = 0.0f;
	}
		

	

	start_air_sound_counter++;

	////////////////////////////////////////////////////////
	//drawing the ground
	DrawGround_scene1();
	
	/*we do not need soulWalkDone to complete so starting directly from outside to inside camera
	momevement*/

	if (!soulWalkStart_scene1)
	{
		if (zRotate_scene1 >= 0.00998f)
		{
			zRotate_scene1 -= 0.005f;
			xRotate_scene1 -= 0.00000021;
			yRotate_scene1 += 0.000001f;

			fprintf_s(gbFile_SSD, "$$$$$$$$$$zRotate=%f, xRotate=%f, yRotate=%f\n", zRotate_scene1, xRotate_scene1, yRotate_scene1);
		}
		
	}

	time_count -= 0.005f;

	/*here we will have a flag which will call 
	a new human which does not walk but and having a color white which flies to nature*/

	if(time_count <= -4.0098f)
	   soulWalkStart_scene1 = true;

	/*moving the camera back to original position after the soul walk has started*/
	if (start_going_back_camera && zRotate_scene1 <= 7.0f)
		zRotate_scene1 += 0.009f;



	/*here we again need to make zrotate at 0.5 when scene3 calls after falling of bird*/
	if (time_count <= -15.0f)
		complete_cut_scene = true;

	if (time_count <= -14.70f)
		*scene_1_completed = true;

	fprintf_s(gbFile, "timeCount=%f\n", time_count);

	//sit_scene1 = false;

	fprintf_s(gbFile, "zRotate=%f\n", zRotate_scene1);


	//creating shadow************************************************
	//creating shadow for tower
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();

	glTranslatef(-3.2f, 0.0f, 4.0f);

	glMultMatrixf((GLfloat *)vShadowMatrix_scene1);

	DrawTower(true);

	glPopMatrix();

	//creating shadow for home
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();

	glTranslatef(-1.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 4.0f);

	glMultMatrixf((GLfloat *)vShadowMatrixHome_scene1);

	DrawHome(true);

	glPopMatrix();

	//creating the model for tower********************
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();

	glTranslatef(-3.20f, 0.0f, 4.0f);

	DrawTower(false);

	glPopMatrix();

	//creating the model for home
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();

	glTranslatef(-1.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 4.0f);
	DrawHome(false);

	glPopMatrix();

	/*glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0, 0.0f);
	HumanAnimation();
	glPopMatrix();*/

	//Human animation************************************************
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);


	glPushMatrix();
	glScalef(0.6f, 0.6f, 0.6f);
	glTranslatef(humanDisplacementX_scene1_human1, humanDisplacementY_scene1_human1, humanDisplacementZ_scene1_human1);
	HumanAnimation_scene1(8.0f, true);
	glPopMatrix();


	if (soulWalkStart_scene1)
	{
		//Second human animation which is a soul***********************************
		glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f);
		glScalef(0.6f, 0.6f, 0.6f);
		glTranslatef(humanDisplacementX_scene1_human2, humanDisplacementY_scene1_human2, humanDisplacementZ_scene1_human2);
		HumanAnimation_scene1(8.0f, false);

		glPopMatrix();

		if (humanDisplacementZ_scene1_human2 <= 12.3003f)
			humanDisplacementZ_scene1_human2 += 0.0081f;
		else
		{
			*scene_1_completed = true;
		}

		if (humanDisplacementY_scene1_human2 <= -0.7f)
			humanDisplacementY_scene1_human2 += 0.005f;

		if (humanDisplacementX_scene1_human2 >= -3.846f)
			humanDisplacementX_scene1_human2 -= 0.0021f;

		if (humanDisplacementZ_scene1_human2 >= 1.5f)
			start_going_back_camera = true;
	}


	//humanDisplacementY=-1.660000
	//humanDisplacement = 12.300003
		//humanDisplacement = -3.849998
	//fprintf_s(gbFile, "humanDisplacementY=%f\n", humanDisplacementY_scene1);
	//fprintf_s(gbFile, "humanDisplacement=%f\n", humanDisplacementZ_scene1);
	//fprintf_s(gbFile, "humanDisplacement=%f\n", humanDisplacementX_scene1);
	//fprintf_s(gbFile, "lightZ=%f, lightX=%f, lightY=%f\n", lightZPos_scene1, lightXPos_scene1, lightYPos_scene1);


}

void DrawGround_scene1(void)
{
	//glTranslatef(0.0f, 0.0f, -3.0f);
	glScalef(0.7f, 0.7f, 0.7f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture_grass_S5);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-18.5f, -1.3f, -10.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-18.5f, -1.3f, 10.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(18.5f, -1.3f, 10.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(18.5f, -1.3f, -10.5f);

	glEnd();

	//glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture_sky_S5);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-18.50f, -1.3f, -12.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(18.50f, -1.3f, -12.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(18.5f, 9.0f, -12.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-18.5f, 9.0f, -12.5f);
	glEnd();

}

void DrawTower(bool drawShadow)
{
	//function declaration
	void SquareRod(GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, bool);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, -3.0f);
	glTranslatef(-1.0f, 0.0f, -1.0f);
	glScalef(0.7f, 0.7f, 0.7f);

	if (!drawShadow)
		glBindTexture(GL_TEXTURE_2D, texture_rock_S5);
	else
		glColor3f(0.0f, 0.0f, 0.0f);

	glRotatef(yRot_scene1, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glVertex3f(-0.7f, 0.50f, 0.6f);
	glVertex3f(-0.7f, 0.50f, -0.6f);
	glVertex3f(0.7f, 0.5f, -0.6f);
	glVertex3f(0.7f, 0.50f, 0.6f);

	glVertex3f(-0.7f, 0.5f, 0.6f);
	glVertex3f(-0.7f, 0.45f, 0.6f);
	glVertex3f(0.7f, 0.45f, 0.6f);
	glVertex3f(0.7f, 0.5f, 0.6f);


	glVertex3f(0.7f, 0.5f, 0.6f);
	glVertex3f(0.7f, 0.45f, 0.6f);
	glVertex3f(0.7f, 0.45f, -0.6f);
	glVertex3f(0.7f, 0.5f, -0.6f);


	glVertex3f(0.7f, 0.5f, -0.6f);
	glVertex3f(0.7f, 0.45f, -0.6f);
	glVertex3f(-0.7f, 0.45f, -0.6f);
	glVertex3f(-0.7f, 0.5f, -0.6f);

	glVertex3f(-0.7f, 0.5f, -0.6f);
	glVertex3f(-0.7f, 0.45f, -0.6f);
	glVertex3f(-0.7f, 0.45f, 0.6f);
	glVertex3f(-0.7f, 0.5f, 0.6f);

	glEnd();

	GLfloat leftLTop[3] = { -0.7f, 0.54f, 0.58f };
	GLfloat leftLBottom[3] = { -0.7f, 0.5f, 0.58f };
	GLfloat leftRBottom[3] = { -0.7f, 0.5f, 0.6f };
	GLfloat leftRTop[3] = { -0.7f, 0.54f, 0.6f };
	GLfloat rightLTop[3] = { 0.7f, 0.54f, 0.6f };
	GLfloat rightLBottom[3] = { 0.7f, 0.5f, 0.6f };
	GLfloat rightRBottom[3] = { 0.7f, 0.5f, 0.58f };
	GLfloat rightRTop[3] = { 0.7f, 0.54f, 0.58f };

	//railings 
	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[1] = 0.62f;
	leftLBottom[1] = 0.58f;
	leftRBottom[1] = 0.58f;
	leftRTop[1] = 0.62f;
	rightLTop[1] = 0.62f;
	rightLBottom[1] = 0.58f;
	rightRBottom[1] = 0.58f;
	rightRTop[1] = 0.62f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[1] = 0.7f;
	leftLBottom[1] = 0.66f;
	leftRBottom[1] = 0.66f;
	leftRTop[1] = 0.7f;
	rightLTop[1] = 0.7f;
	rightLBottom[1] = 0.66f;
	rightRBottom[1] = 0.66f;
	rightRTop[1] = 0.7f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	GLfloat leftLTopR[3] = { 0.7f, 0.54f, 0.58f };
	GLfloat leftLBottomR[3] = { 0.7f, 0.5f, 0.58f };
	GLfloat leftRBottomR[3] = { 0.7f, 0.5f, 0.6f };
	GLfloat leftRTopR[3] = { 0.7f, 0.54f, 0.6f };
	GLfloat rightLTopR[3] = { 0.7f, 0.54f, -0.6f };
	GLfloat rightLBottomR[3] = { 0.7f, 0.5f, -0.6f };
	GLfloat rightRBottomR[3] = { 0.7f, 0.5f, -0.58f };
	GLfloat rightRTopR[3] = { 0.7f, 0.54f, -0.58f };

	SquareRod(leftLTopR, leftLBottomR, leftRBottomR, leftRTopR, rightLTopR, rightLBottomR, rightRBottomR, rightRTopR, drawShadow);

	leftLTopR[1] = 0.62f;
	leftLBottomR[1] = 0.58f;
	leftRBottomR[1] = 0.58f;
	leftRTopR[1] = 0.62f;
	rightLTopR[1] = 0.62f;
	rightLBottomR[1] = 0.58f;
	rightRBottomR[1] = 0.58f;
	rightRTopR[1] = 0.62f;

	SquareRod(leftLTopR, leftLBottomR, leftRBottomR, leftRTopR, rightLTopR, rightLBottomR, rightRBottomR, rightRTopR, drawShadow);

	leftLTopR[1] = 0.7f;
	leftLBottomR[1] = 0.66f;
	leftRBottomR[1] = 0.66f;
	leftRTopR[1] = 0.7f;
	rightLTopR[1] = 0.7f;
	rightLBottomR[1] = 0.66f;
	rightRBottomR[1] = 0.66f;
	rightRTopR[1] = 0.7f;

	SquareRod(leftLTopR, leftLBottomR, leftRBottomR, leftRTopR, rightLTopR, rightLBottomR, rightRBottomR, rightRTopR, drawShadow);

	GLfloat leftLTopB[3] = { -0.7f, 0.54f, -0.58f };
	GLfloat leftLBottomB[3] = { -0.7f, 0.5f, -0.58f };
	GLfloat leftRBottomB[3] = { -0.7f, 0.5f, -0.6f };
	GLfloat leftRTopB[3] = { -0.7f, 0.54f, -0.6f };
	GLfloat rightLTopB[3] = { -0.7f, 0.54f, 0.6f };
	GLfloat rightLBottomB[3] = { -0.7f, 0.5f, 0.6f };
	GLfloat rightRBottomB[3] = { -0.7f, 0.5f, 0.58f };
	GLfloat rightRTopB[3] = { -0.7f, 0.54f, 0.58f };


	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[1] = 0.62f;
	leftLBottomB[1] = 0.58f;
	leftRBottomB[1] = 0.58f;
	leftRTopB[1] = 0.62f;
	rightLTopB[1] = 0.62f;
	rightLBottomB[1] = 0.58f;
	rightRBottomB[1] = 0.58f;
	rightRTopB[1] = 0.62f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[1] = 0.7f;
	leftLBottomB[1] = 0.66f;
	leftRBottomB[1] = 0.66f;
	leftRTopB[1] = 0.7f;
	rightLTopB[1] = 0.7f;
	rightLBottomB[1] = 0.66f;
	rightRBottomB[1] = 0.66f;
	rightRTopB[1] = 0.7f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = -0.68f;
	leftLTopB[1] = 0.7f;
	leftLTopB[2] = -0.58f;
	leftLBottomB[0] = -0.68f;
	leftLBottomB[1] = 0.7f;
	leftLBottomB[2] = -0.6f;
	leftRBottomB[0] = -0.7f;
	leftRBottomB[1] = 0.7f;
	leftRBottomB[2] = -0.6f;
	leftRTopB[0] = -0.7f;
	leftRTopB[1] = 0.7f;
	leftRTopB[2] = -0.58f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = 0.5f;
	rightLTopB[2] = -0.58f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = 0.5f;
	rightLBottomB[2] = -0.6f;
	rightRBottomB[0] = -0.68f;
	rightRBottomB[1] = 0.5f;
	rightRBottomB[2] = -0.6f;
	rightRTopB[0] = -0.68f;
	rightRTopB[1] = 0.5f;
	rightRTopB[2] = -0.6f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);


	leftLTopB[0] = 0.7f;
	leftLTopB[1] = 0.7f;
	leftLTopB[2] = -0.58f;
	leftLBottomB[0] = 0.7f;
	leftLBottomB[1] = 0.7f;
	leftLBottomB[2] = -0.6f;
	leftRBottomB[0] = 0.68f;
	leftRBottomB[1] = 0.7f;
	leftRBottomB[2] = -0.6f;
	leftRTopB[0] = 0.68f;
	leftRTopB[1] = 0.7f;
	leftRTopB[2] = -0.58f;

	rightLTopB[0] = 0.68f;
	rightLTopB[1] = 0.5f;
	rightLTopB[2] = -0.58f;
	rightLBottomB[0] = 0.68f;
	rightLBottomB[1] = 0.5f;
	rightLBottomB[2] = -0.6f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = 0.5f;
	rightRBottomB[2] = -0.6f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = 0.5f;
	rightRTopB[2] = -0.6f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//Central rest room for watch tower

	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.95f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.95f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.95f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.95f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.5f;
	rightLTopB[1] = 0.5f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = -0.5f;
	rightLBottomB[1] = 0.5f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.5f;
	rightRBottomB[1] = 0.5f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.5f;
	rightRTopB[1] = 0.5f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//roof
	leftLTopB[0] = 0.7f;
	leftLTopB[1] = 0.980f;
	leftLTopB[2] = 0.6f;
	leftLBottomB[0] = 0.7f;
	leftLBottomB[1] = 0.980f;
	leftLBottomB[2] = -0.6f;
	leftRBottomB[0] = -0.7f;
	leftRBottomB[1] = 0.980f;
	leftRBottomB[2] = -0.6f;
	leftRTopB[0] = -0.7f;
	leftRTopB[1] = 0.980f;
	leftRTopB[2] = 0.6f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = 0.95f;
	rightLTopB[2] = 0.6f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = 0.95f;
	rightLBottomB[2] = -0.6f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = 0.95f;
	rightRBottomB[2] = -0.6f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = 0.95f;
	rightRTopB[2] = 0.6f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	glBegin(GL_QUADS);

	glVertex3f(0.7f, 0.980f, 0.6f);
	glVertex3f(0.7f, 0.980f, -0.6f);
	glVertex3f(-0.7f, 0.980f, -0.6f);
	glVertex3f(-0.7f, 0.980f, 0.6f);

	glVertex3f(0.7f, 0.950f, 0.6f);
	glVertex3f(0.7f, 0.950f, -0.6f);
	glVertex3f(-0.7f, 0.950f, -0.6f);
	glVertex3f(-0.7f, 0.950f, 0.6f);

	glEnd();

	//Lower support
	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = 0.41f;
	leftRBottomB[0] = 0.45f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = 0.41f;
	leftRTopB[0] = 0.45f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.65f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = 0.65f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = 0.41f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = 0.41f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = -0.41f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = 0.45f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = 0.45f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = -0.41f;

	rightLTopB[0] = 0.65f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = -0.41f;
	rightLBottomB[0] = 0.65f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.7f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.7f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = -0.41f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = -0.45f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = -0.41f;
	leftLBottomB[0] = -0.45f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = -0.41f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = -0.41f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.65f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.65f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = -0.41f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	leftLTopB[0] = -0.45f;
	leftLTopB[1] = 0.5f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.45f;
	leftLBottomB[1] = 0.5f;
	leftLBottomB[2] = 0.41f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.5f;
	leftRBottomB[2] = 0.41f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.5f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.7f;
	rightLTopB[1] = -1.30f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = -0.7f;
	rightLBottomB[1] = -1.30f;
	rightLBottomB[2] = 0.41f;
	rightRBottomB[0] = -0.65f;
	rightRBottomB[1] = -1.30f;
	rightRBottomB[2] = 0.41f;
	rightRTopB[0] = -0.65f;
	rightRTopB[1] = -1.30f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//truss for lower support
	//A1
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A2
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C1
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C2
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B1
	leftLTopB[0] = 0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B2
	leftLTopB[0] = 0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D1
	leftLTopB[0] = -0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D2
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//cross truss bars

	//A0-A1
	leftLTopB[0] = -0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A1-A0
	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = 0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = -0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = -0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B0-B1
	leftLTopB[0] = 0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B1-B0
	leftLTopB[0] = 0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = 0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = 0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = 0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.45f;

	rightLTopB[0] = 0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = 0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.45f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//c0-c1
	leftLTopB[0] = -0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C1-C0
	leftLTopB[0] = 0.5f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = 0.5f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = 0.5f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = 0.5f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = -0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = -0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D0-D1
	leftLTopB[0] = -0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D1-D0
	leftLTopB[0] = -0.52f;
	leftLTopB[1] = 0.48f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.52f;
	leftLBottomB[1] = 0.43f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = 0.43f;
	leftRBottomB[2] = -0.45f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = 0.48f;
	leftRTopB[2] = -0.45f;

	rightLTopB[0] = -0.58f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.45f;
	rightLBottomB[0] = -0.58f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.45f;
	rightRBottomB[0] = -0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = -0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A1-A2
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//A2-A1
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = 0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = 0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = 0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = 0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B1-B2
	leftLTopB[0] = 0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//B2-B1
	leftLTopB[0] = 0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = 0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = 0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = 0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = 0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C1-C2
	leftLTopB[0] = -0.55f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.55f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.55f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.55f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.6f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.6f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//C2-C1
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = -0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = -0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = -0.47f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = -0.47f;

	rightLTopB[0] = 0.55f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.47f;
	rightLBottomB[0] = 0.55f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.47f;
	rightRBottomB[0] = 0.55f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = 0.55f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

	//D1-D2
	leftLTopB[0] = -0.57f;
	leftLTopB[1] = -0.1f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.57f;
	leftLBottomB[1] = -0.15f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.6f;
	leftRBottomB[1] = -0.15f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.6f;
	leftRTopB[1] = -0.1f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.63f;
	rightLTopB[1] = -0.60f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.63f;
	rightLBottomB[1] = -0.650f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.6f;
	rightRBottomB[1] = -0.650f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.6f;
	rightRTopB[1] = -0.60f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);


	//D2-D1
	leftLTopB[0] = -0.6f;
	leftLTopB[1] = -0.6f;
	leftLTopB[2] = 0.45f;
	leftLBottomB[0] = -0.6f;
	leftLBottomB[1] = -0.65f;
	leftLBottomB[2] = 0.45f;
	leftRBottomB[0] = -0.63f;
	leftRBottomB[1] = -0.65f;
	leftRBottomB[2] = 0.45f;
	leftRTopB[0] = -0.63f;
	leftRTopB[1] = -0.6f;
	leftRTopB[2] = 0.45f;

	rightLTopB[0] = -0.6f;
	rightLTopB[1] = -0.10f;
	rightLTopB[2] = -0.45f;
	rightLBottomB[0] = -0.6f;
	rightLBottomB[1] = -0.150f;
	rightLBottomB[2] = -0.45f;
	rightRBottomB[0] = -0.57f;
	rightRBottomB[1] = -0.150f;
	rightRBottomB[2] = -0.45f;
	rightRTopB[0] = -0.57f;
	rightRTopB[1] = -0.10f;
	rightRTopB[2] = -0.45f;

	SquareRod(leftLTopB, leftLBottomB, leftRBottomB, leftRTopB, rightLTopB, rightLBottomB, rightRBottomB, rightRTopB, drawShadow);

}

void DrawHome(bool drawShadow)
{

	//function declaration
	void SquareRod(GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, bool);

	glRotatef(yRot_scene1, 0.0f, 1.0f, 0.0f);
	glScalef(1.2f, 1.2f, 1.2f);
	glTranslatef(1.0f, 0.0f, -4.0f);


	glBindTexture(GL_TEXTURE_2D, texture_brick_S5);

	GLfloat leftLTop[3] = { 1.0f, 0.40f, 0.1f };
	GLfloat leftLBottom[3] = { 1.0f, 0.40f, -2.1f };
	GLfloat leftRBottom[3] = { -1.0f, 0.40f, -2.1f };
	GLfloat leftRTop[3] = { -1.0f, 0.40f, 0.1f };

	GLfloat rightLTop[3] = { -1.0f, -1.0f, 0.1f };
	GLfloat rightLBottom[3] = { -1.0f, -1.0f, -2.1f };
	GLfloat rightRBottom[3] = { 1.0f, -1.0f, -2.1f };
	GLfloat rightRTop[3] = { 1.0f, -1.0f, 0.1f };

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);


	leftLTop[0] = 0.5f;
	leftLTop[1] = 1.5f;
	leftLTop[2] = -0.3f;
	leftLBottom[0] = 0.50f;
	leftLBottom[1] = 1.5f;
	leftLBottom[2] = -2.1f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 1.5f;
	leftRBottom[2] = -2.1f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 1.5f;
	leftRTop[2] = -0.3f;

	rightLTop[0] = -1.0f;
	rightLTop[1] = 0.4f;
	rightLTop[2] = -0.3f;
	rightLBottom[0] = -1.0f;
	rightLBottom[1] = 0.4f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.5f;
	rightRBottom[1] = 0.4f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.5f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = -0.3f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = -0.25f;
	leftLTop[1] = 2.0f;
	leftLTop[2] = -2.3f;
	leftLBottom[0] = -0.250f;
	leftLBottom[1] = 2.0f;
	leftLBottom[2] = -2.3f;
	leftRBottom[0] = -1.20f;
	leftRBottom[1] = 1.3f;
	leftRBottom[2] = -2.3f;
	leftRTop[0] = -1.20f;
	leftRTop[1] = 1.4f;
	leftRTop[2] = -2.3f;

	rightLTop[0] = -1.20f;
	rightLTop[1] = 1.4f;
	rightLTop[2] = -0.2f;
	rightLBottom[0] = -1.20f;
	rightLBottom[1] = 1.3f;
	rightLBottom[2] = -0.2f;
	rightRBottom[0] = -0.25f;
	rightRBottom[1] = 2.0f;
	rightRBottom[2] = -0.2f;
	rightRTop[0] = -0.20f;
	rightRTop[1] = 2.0f;
	rightRTop[2] = -0.2f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.7f;
	leftLTop[1] = 1.40f;
	leftLTop[2] = -2.3f;
	leftLBottom[0] = 0.70f;
	leftLBottom[1] = 1.350f;
	leftLBottom[2] = -2.3f;
	leftRBottom[0] = -0.250f;
	leftRBottom[1] = 2.0f;
	leftRBottom[2] = -2.3f;
	leftRTop[0] = -0.250f;
	leftRTop[1] = 2.0f;
	leftRTop[2] = -2.3f;

	rightLTop[0] = -0.250f;
	rightLTop[1] = 2.0f;
	rightLTop[2] = -0.2f;
	rightLBottom[0] = -0.250f;
	rightLBottom[1] = 2.0f;
	rightLBottom[2] = -0.2f;
	rightRBottom[0] = 0.70f;
	rightRBottom[1] = 1.350f;
	rightRBottom[2] = -0.2f;
	rightRTop[0] = 0.7f;
	rightRTop[1] = 1.40f;
	rightRTop[2] = -0.2f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	//upper triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, 1.5f, -0.3f);
	glVertex3f(0.5f, 1.5f, -0.3f);
	glVertex3f(-0.25f, 2.0f, -0.3f);

	glVertex3f(-1.0f, 1.5f, -2.1f);
	glVertex3f(0.5f, 1.5f, -2.1f);
	glVertex3f(-0.25f, 2.0f, -2.1f);

	glEnd();

	//railing
	leftLTop[0] = -1.0f;
	leftLTop[1] = 0.50f;
	leftLTop[2] = 0.09f;
	leftLBottom[0] = -1.0f;
	leftLBottom[1] = 0.4750f;
	leftLBottom[2] = 0.09f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 0.4750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 0.50f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.50f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.4750f;
	rightLBottom[2] = 0.1f;
	rightRBottom[0] = 1.0f;
	rightRBottom[1] = 0.4750f;
	rightRBottom[2] = 0.09f;
	rightRTop[0] = 1.0f;
	rightRTop[1] = 0.5f;
	rightRTop[2] = 0.09f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = -1.0f;
	leftLTop[1] = 0.60f;
	leftLTop[2] = 0.09f;
	leftLBottom[0] = -1.0f;
	leftLBottom[1] = 0.5750f;
	leftLBottom[2] = 0.09f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 0.5750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 0.60f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.60f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.5750f;
	rightLBottom[2] = 0.1f;
	rightRBottom[0] = 1.0f;
	rightRBottom[1] = 0.5750f;
	rightRBottom[2] = 0.09f;
	rightRTop[0] = 1.0f;
	rightRTop[1] = 0.6f;
	rightRTop[2] = 0.09f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.990f;
	leftLTop[1] = 0.50f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = 0.990f;
	leftLBottom[1] = 0.4750f;
	leftLBottom[2] = 0.1f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.4750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.50f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.50f;
	rightLTop[2] = -2.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.4750f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.990f;
	rightRBottom[1] = 0.4750f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.990f;
	rightRTop[1] = 0.5f;
	rightRTop[2] = -2.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.990f;
	leftLTop[1] = 0.60f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = 0.990f;
	leftLBottom[1] = 0.5750f;
	leftLBottom[2] = 0.1f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.5750f;
	leftRBottom[2] = 0.1f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.60f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.60f;
	rightLTop[2] = -2.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.5750f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.990f;
	rightRBottom[1] = 0.5750f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.990f;
	rightRTop[1] = 0.6f;
	rightRTop[2] = -2.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.90f;
	leftLTop[1] = 0.650f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = 0.90f;
	leftLBottom[1] = 0.65f;
	leftLBottom[2] = 0.08f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.650f;
	leftRBottom[2] = 0.08f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.650f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.40f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.70f;
	rightLBottom[2] = 0.08f;
	rightRBottom[0] = 0.90f;
	rightRBottom[1] = 0.70f;
	rightRBottom[2] = 0.08f;
	rightRTop[0] = 0.90f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = 0.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = -0.90f;
	leftLTop[1] = 0.650f;
	leftLTop[2] = 0.1f;
	leftLBottom[0] = -0.90f;
	leftLBottom[1] = 0.65f;
	leftLBottom[2] = 0.08f;
	leftRBottom[0] = -1.0f;
	leftRBottom[1] = 0.650f;
	leftRBottom[2] = 0.08f;
	leftRTop[0] = -1.0f;
	leftRTop[1] = 0.650f;
	leftRTop[2] = 0.1f;

	rightLTop[0] = -1.0f;
	rightLTop[1] = 0.40f;
	rightLTop[2] = 0.1f;
	rightLBottom[0] = -1.0f;
	rightLBottom[1] = 0.70f;
	rightLBottom[2] = 0.08f;
	rightRBottom[0] = -0.90f;
	rightRBottom[1] = 0.70f;
	rightRBottom[2] = 0.08f;
	rightRTop[0] = -0.90f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = 0.1f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	leftLTop[0] = 0.90f;
	leftLTop[1] = 0.650f;
	leftLTop[2] = -2.08f;
	leftLBottom[0] = 0.90f;
	leftLBottom[1] = 0.65f;
	leftLBottom[2] = -2.1f;
	leftRBottom[0] = 1.0f;
	leftRBottom[1] = 0.650f;
	leftRBottom[2] = -2.1f;
	leftRTop[0] = 1.0f;
	leftRTop[1] = 0.650f;
	leftRTop[2] = -2.08f;

	rightLTop[0] = 1.0f;
	rightLTop[1] = 0.40f;
	rightLTop[2] = -2.08f;
	rightLBottom[0] = 1.0f;
	rightLBottom[1] = 0.70f;
	rightLBottom[2] = -2.1f;
	rightRBottom[0] = 0.90f;
	rightRBottom[1] = 0.70f;
	rightRBottom[2] = -2.1f;
	rightRTop[0] = 0.90f;
	rightRTop[1] = 0.4f;
	rightRTop[2] = -2.08f;

	SquareRod(leftLTop, leftLBottom, leftRBottom, leftRTop, rightLTop, rightLBottom, rightRBottom, rightRTop, drawShadow);

	//Door

	glBindTexture(GL_TEXTURE_2D, texture_door_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3f, 0.1f, 0.12f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, -1.0f, 0.12f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.3f, -1.0f, 0.12f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.3f, 0.1f, 0.12f);



	//window
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.01f, 0.071f, -0.25f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.01f, -0.70f, -0.25f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.01f, -0.70f, -1.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.01f, 0.071f, -1.5f);

	glEnd();

	/*GLfloat leftLTop[3] = { 1.0f, 0.40f, 0.1f };
	GLfloat leftLBottom[3] = { 1.0f, 0.40f, -2.1f };
	GLfloat leftRBottom[3] = { -1.0f, 0.40f, -2.1f };
	GLfloat leftRTop[3] = { -1.0f, 0.40f, 0.1f };*/

	glBindTexture(GL_TEXTURE_2D, texture_brick_S5);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 0.40f, 0.1f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 0.40f, -2.1f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 0.40f, -2.1f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 0.40f, 0.1f);

	glEnd();


}

void HumanAnimation_scene1(GLfloat speed, bool sit_scene1)
{

	//function declaration
	void WalkHuman_scene1(bool, GLfloat);
	void DrawSphere_scene1(GLfloat, GLfloat, GLfloat, GLfloat);

	glRotatef(yTrans_scene1, 0.0f, 1.0f, 0.0f);

	//if (!sit_scene1)
		//WalkHuman_scene1(true, speed);

	//************************************************************************************
	//head
	glPushMatrix();
	glScalef(1.0f, 1.4f, 1.0f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluSphere(quadric_SSD, 0.1f, 20, 20);
	glPopMatrix();

	//*************************************************************************************
	//neck
	glPushMatrix();
	glTranslatef(0.0f, 0.62f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.028f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluCylinder(quadric_SSD, 0.06f, 0.06f, 0.09f, 10, 10);
	glPopMatrix();

	//**************************************************************************************
	//body
	//neck to main body slant height
	glPushMatrix();
	glTranslatef(0.0f, 0.55f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.02f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.4f, 0.80f, 1.0f);
	quadric_SSD = gluNewQuadric();
	gluCylinder(quadric_SSD, 0.06f, 0.14f, 0.051f, 20, 20);

	//main body
	glPushMatrix();
	glScalef(1.0f, 1.21f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.06f);
	quadric_SSD = gluNewQuadric();
	gluCylinder(quadric_SSD, 0.125f, 0.1f, 0.4f, 20, 20);

	glPopMatrix();
	glPopMatrix();

	//***************************************************************************************
	//hands
	//left hand**************************
	glPushMatrix();
	glTranslatef(-0.19f, 0.0f, 0.0f); //-0.19
	glTranslatef(0.0f, 0.49f, 0.0f);

	if (sit_scene1)
	{
		glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.19f, 0.0f);
		glScalef(1.0f, 4.7f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.042f, 20, 20);

	}
	else
	{
		glRotatef(leftWalkAngleHandHuman_scene1, 1.0f, 0.0f, 0.0f);//0.37
		glTranslatef(0.0f, -0.13f, 0.0f);
		glScalef(1.0f, 3.8f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.038f, 20, 20);
	}


	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//lower arm
	glPushMatrix();
	glTranslatef(0.0f, -0.05f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluSphere(quadric_SSD, 0.032f, 20, 20);
	glPopMatrix();

	glPopMatrix();

	//right hand*******************
	glPushMatrix();
	glTranslatef(0.19f, 0.0f, 0.0f); //-0.19
	glTranslatef(0.0f, 0.49f, 0.0f);
	if (sit_scene1)
	{
		glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.19f, 0.0f);
		glScalef(1.0f, 4.7f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.042f, 20, 20);

	}
	else
	{
		glRotatef(rightWalkAngleHandHuman_scene1, 1.0f, 0.0f, 0.0f);//0.37
		glTranslatef(0.0f, -0.13f, 0.0f);
		glScalef(1.0f, 3.8f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.038f, 20, 20);
	}



	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//lower arm
	glPushMatrix();
	glTranslatef(0.0f, -0.05f, 0.0f);
	quadric_SSD = gluNewQuadric();
	gluSphere(quadric_SSD, 0.032f, 20, 20);
	glPopMatrix();

	glPopMatrix();

	//***************************************************************************
	//legs
	//left leg**********************
	glPushMatrix();

	if (sit_scene1)
	{
		glTranslatef(-0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.03f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25, 4.3f);
		DrawSphere_scene1(0.072f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		glTranslatef(-0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.08f, 0.0f);
		glRotatef(leftWalkAngleHuman_scene1, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25f, 4.3f);
		DrawSphere_scene1(0.072f, 0.0f, 0.0f, 0.0f);
	}

	//lower leg

	if (sit_scene1)
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 0.061f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(4.30f, 1.250f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.056f, 20, 20);
	}
	else
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.046f, 20, 20);
	}



	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//*******************************
	//foot
	if (!sit_scene1)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.032800f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(1.0f, 2.50f, 1.0f);
		glTranslatef(0.0f, 0.022f, 0.02f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.04f, 10, 10);
		glPopMatrix();
	}


	glPopMatrix();

	glPopMatrix();

	//right leg**********************
	glPushMatrix();

	if (sit_scene1)
	{
		glTranslatef(0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.03f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25, 4.3f);
		DrawSphere_scene1(0.072f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		glTranslatef(0.075f, 0.0f, -0.021f);
		glTranslatef(0.0f, 0.08f, 0.0f);
		glRotatef(rightWalkAngleHuman_scene1, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.25f, 4.3f);
		DrawSphere_scene1(0.072f, 0.0f, 0.0f, 0.0f);
	}




	//lower leg

	if (sit_scene1)
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 0.061f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(4.30f, 1.250f, 1.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.056f, 20, 20);
	}
	else
	{
		glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.046f, 20, 20);
	}

	//fprintf_s(gbFile_SSD, "%f==xAngle\n%f==xTrans\n", xAngle, xTrans);

	//*******************************
	//foot

	if (!sit_scene1)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.032800f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.0f / 1.25f, 1.0f / 4.3f);
		glScalef(1.0f, 2.50f, 1.0f);
		glTranslatef(0.0f, 0.022f, 0.02f);
		quadric_SSD = gluNewQuadric();
		gluSphere(quadric_SSD, 0.04f, 10, 10);
		glPopMatrix();
	}

	glPopMatrix();

	glPopMatrix();



}

void DrawSphere_scene1(GLfloat radius, GLfloat X1, GLfloat Y1, GLfloat Z1)
{
	GLfloat x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLfloat a, b;
	GLfloat grade = 40;

	for (a = 0.0f; a <= GL_PI / 1.90f; a += (GL_PI / grade))
	{
		glBegin(GL_POLYGON);

		for (b = 0.0f; b <= 2.0f * GL_PI; b += (GL_PI / grade))
		{
			x1 = radius * cos(b) * sin(a);
			y1 = radius * sin(b) * sin(a);
			z1 = radius * cos(a);

			glVertex3f(x1 + X1, y1 + Y1, z1 + Z1);

			x2 = radius * cos(b + (GL_PI / grade)) * sin(a);
			y2 = radius * sin(b + (GL_PI / grade)) * sin(a);
			z2 = radius * cos(a);

			glVertex3f(x2 + X1, y2 + Y1, z2 + Z1);

			x3 = radius * cos(b) * sin(a + (GL_PI / grade));
			y3 = radius * sin(b) * sin(a + (GL_PI / grade));
			z3 = radius * cos(a + (GL_PI / grade));

			glVertex3f(x3 + X1, y3 + Y1, z3 + Z1);

			x4 = radius * cos(b + (GL_PI / grade)) * sin(a + (GL_PI / grade));
			y4 = radius * sin(b + (GL_PI / grade)) * sin(a + (GL_PI / grade));
			z4 = radius * cos(a + (GL_PI / grade));

			glVertex3f(x4 + X1, y4 + Y1, z4 + Z1);


			//
		}

		glEnd();
	}
}

void WalkHuman_scene1(bool walk, GLfloat speed)
{
	static bool leftLegWalk = true;
	static bool rightLegWalk = false;
	static bool rightLegReturn = true;
	static bool leftLegReturn = false;

	if (walk)
	{
		if (leftLegWalk)
		{
			if (leftWalkAngleHandHuman_scene1 > -40.0f)
			{
				leftWalkAngleHandHuman_scene1 -= (0.102f * speed);
			}

			if (leftWalkAngleHuman_scene1 < 20.0f)
			{
				leftWalkAngleHuman_scene1 += (0.051f * speed);
			}
			else
			{
				leftLegReturn = true;
				leftLegWalk = false;
			}


		}
		if (rightLegWalk)
		{
			if (rightWalkAngleHandHuman_scene1 > -40.0f)
			{
				rightWalkAngleHandHuman_scene1 -= (0.102f * speed);
			}

			if (rightWalkAngleHuman_scene1 < 20.0f)
			{
				rightWalkAngleHuman_scene1 += (0.051f * speed);
			}
			else
			{
				rightLegReturn = true;
				rightLegWalk = false;
			}

		}
		if (leftLegReturn)
		{
			if (leftWalkAngleHandHuman_scene1 < 40.0f)
			{
				leftWalkAngleHandHuman_scene1 += (0.102f * speed);
			}

			if (leftWalkAngleHuman_scene1 > -20.0f)
			{
				leftWalkAngleHuman_scene1 -= (0.051f * speed);
			}
			else
			{
				leftLegReturn = false;
				leftLegWalk = true;
			}
		}
		if (rightLegReturn)
		{
			if (rightWalkAngleHandHuman_scene1 < 40.0f)
			{
				rightWalkAngleHandHuman_scene1 += (0.102f * speed);
			}

			if (rightWalkAngleHuman_scene1 > -20.0f)
			{
				rightWalkAngleHuman_scene1 -= (0.051f * speed);
			}
			else
			{
				rightLegReturn = false;
				rightLegWalk = true;
			}
		}

	}

}


void Uninitialize(void)
{
	//function declaration
	//here pass shadow as false and number of branches as 0 since it is called to free the malloc memory
	void DrawTree_S5(bool shadow, GLint numberOfBranches);
	void DrawTree__S5(bool shadow, GLint numberOfBranches);
	void DrawTree(bool shadow, GLint numberOfBranches);
	void DrawTree_(bool, GLint);

	//file IO code

	if (gbFullScreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));

		SetWindowPlacement(ghwnd, &wPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE);
		ShowCursor(TRUE);
		gbFullScreen = false;
	}

	unitialize = true;

	 DrawTree_S5(false, 0);
	 DrawTree__S5(false, 0);
	 DrawTree(false, 0);
	 DrawTree_(false, 0);

	if (wglGetCurrentContext() == hglrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (hglrc)
	{
		wglDeleteContext(hglrc);
		hglrc = NULL;
	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (gbFile)
	{
		fprintf_s(gbFile, "log file closed successfully\n");
		fclose(gbFile);
		gbFile = NULL;
	}

	if (gbFile_SSD)
	{
		fprintf_s(gbFile_SSD, "log file closed successfully\n");
		fclose(gbFile_SSD);
		gbFile_SSD = NULL;
	}


	if (texture_grass_S5)
	{
		glDeleteTextures(1, &texture_grass_S5);
	}

	if (texture_sky_S5)
	{
		glDeleteTextures(1, &texture_sky_S5);
	}

	if (stem_texture_S5)
	{
		glDeleteTextures(1, &stem_texture_S5);
	}

	if (texture_feather_S5)
		glDeleteTextures(1, &texture_feather_S5);

	if (mahadev_tex_S5)
		glDeleteTextures(1, &mahadev_tex_S5);


	if (texture_brick_S5)
	{
		glDeleteTextures(1, &texture_brick_S5);
	}

	if (texture_rock_S5)
	{
		glDeleteTextures(1, &texture_rock_S5);
	}

	if (texture_door_S5)
	{
		glDeleteTextures(1, &texture_door_S5);
	}

	if (side_texture_S5)
	{
		glDeleteTextures(1, &side_texture_S5);
	}

	if (texture_lightning_S5)
	{
		glDeleteTextures(1, &texture_lightning_S5);
	}

	
	if (nature_texture)
	{
		glDeleteTextures(1, &nature_texture);
	}

	if (nature1_texture)
	{
		glDeleteTextures(1, &nature1_texture);
	}

	if (text_ECredit_1)
	{
		glDeleteTextures(1, &text_ECredit_1);
	}

	if (text_ECredit_2)
	{
		glDeleteTextures(1, &text_ECredit_2);
	}

	if (text_ECredit_3)
	{
		glDeleteTextures(1, &text_ECredit_3);
	}

	if (text_title_1)
	{
		glDeleteTextures(1, &text_title_1);
	}

	if (text_title_2)
	{
		glDeleteTextures(1, &text_title_2);
	}

	if (text_title_3)
	{
		glDeleteTextures(1, &text_title_3);
	}

	if (trishul_tex_S5)
	{
		glDeleteTextures(1, &trishul_tex_S5);
	}
}













