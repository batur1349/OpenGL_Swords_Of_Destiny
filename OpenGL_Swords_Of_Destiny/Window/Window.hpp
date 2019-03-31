#ifndef WINDOW_H
#define WINDOW_H

constexpr auto FRAME_CONTAINER_SIZE = 60;
using _Clock = std::chrono::steady_clock;

class Window
{
public:
	// Constructor and destructor
	Window(const unsigned int& width, const unsigned int& height, const std::string& title);
	~Window();

	// Functions
	void Close();
	void Update();
	void ShowFps();

	// Getters
	const bool& IsOpen() const;
	const float& GetAspectRatio() const;
	const float& GetDeltatime() const;
	const unsigned int& GetFramelimit() const;
	const glm::vec2& GetMousepositionScreen() const;
	const glm::vec2& GetMousepositionWindow() const;
	const glm::vec2& GetMousepositionOpenGL() const;
	const unsigned int& GetScreenWidth() const;
	const unsigned int& GetScreenHeight() const;

	// Setters
	void SetMsTitle(const std::string& msTitle);
	void SetSize(const unsigned int& width, const unsigned int& height);
	void SetVsync(const unsigned int& value);
	void SetFramelimit(const unsigned int& limit);
private:
	// Functions
	void UpdateMousepositions();

	// Variables
	GLFWwindow*			_window;
	std::string			_title;
	std::string			_msTitle;
	float				_aspectRatio;
	unsigned int		_screenWidth;
	unsigned int		_screenHeight;
	float				_deltaTime;
	std::vector<float>	_oldFrames;
	unsigned int		_frameLimit;

	glm::vec2			_mousePositionWindow;
	glm::vec2			_mousePositionScreen;
	glm::vec2			_mousePositionOpenGL;
};
#endif // !WINDOW_H