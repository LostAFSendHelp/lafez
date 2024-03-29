#include <lafez/platform_headers/lafez_gl.hpp>
#include <lafez/utils/Log.hpp>
#include "Key.hpp"

namespace Lafez {
	Key* Key::sShared = nullptr;

	void Key::startUp(GraphicsAPI platform) {
		LZ_ENGINE_GUARD_VOID(!sShared, "ABORTING ATTEMPT TO DOUBLE STARTUP KEYCODE SET...");
		sShared = new Key(platform);
	}

	void Key::shutDown() {
		LZ_ENGINE_GUARD_VOID(sShared, "ABORTING ATTEMPT TO DOUBLE SHUTDOWN KEYCODE SET...");
		delete sShared;
		LZ_ENGINE_INFO("KEYCODE SET RESET");
	}

	Key* Key::getInstance() {
		LZ_ENGINE_ASSERT(sShared, "KEYCODE SET NOT INITIALIZED");
		return sShared;
	}

	// TODO: init for different platforms
	Key::Key(GraphicsAPI platform):
		// ALPHABETS
		A(GLFW_KEY_A), B(GLFW_KEY_B), C(GLFW_KEY_C), D(GLFW_KEY_D),
		E(GLFW_KEY_E), F(GLFW_KEY_F), G(GLFW_KEY_G), H(GLFW_KEY_H),
		I(GLFW_KEY_I), J(GLFW_KEY_J), K(GLFW_KEY_K), L(GLFW_KEY_L),
		M(GLFW_KEY_M), N(GLFW_KEY_N), O(GLFW_KEY_O), P(GLFW_KEY_P),
		Q(GLFW_KEY_Q), R(GLFW_KEY_R), S(GLFW_KEY_S), T(GLFW_KEY_T),
		U(GLFW_KEY_U), V(GLFW_KEY_V), W(GLFW_KEY_W), X(GLFW_KEY_X),
		Y(GLFW_KEY_Y), Z(GLFW_KEY_Z), 
		
		// FUNCTIONS
		F1(GLFW_KEY_F1), F2(GLFW_KEY_F2), F3(GLFW_KEY_F3),
		F4(GLFW_KEY_F4), F5(GLFW_KEY_F5), F6(GLFW_KEY_F6),
		F7(GLFW_KEY_F7), F8(GLFW_KEY_F8), F9(GLFW_KEY_F9),
		F10(GLFW_KEY_F10), F11(GLFW_KEY_F11), F12(GLFW_KEY_F12),

		// ARROWS
		UP(GLFW_KEY_UP), DOWN(GLFW_KEY_DOWN), LEFT(GLFW_KEY_LEFT), RIGHT(GLFW_KEY_RIGHT),

		// CONTROLS
		ESCAPE(GLFW_KEY_ESCAPE), TAB(GLFW_KEY_TAB), L_SHIFT(GLFW_KEY_LEFT_SHIFT),
		R_SHIFT(GLFW_KEY_RIGHT_SHIFT), L_CTRL(GLFW_KEY_LEFT_CONTROL),
		R_CTRL(GLFW_KEY_RIGHT_CONTROL), L_ALT(GLFW_KEY_LEFT_ALT),
		R_ALT(GLFW_KEY_RIGHT_ALT), L_ENTER(GLFW_KEY_ENTER), R_ENTER(GLFW_KEY_KP_ENTER),

		// NUMBERS
		K1(GLFW_KEY_1), K2(GLFW_KEY_2), K3(GLFW_KEY_3), K4(GLFW_KEY_4), K5(GLFW_KEY_5),
		K6(GLFW_KEY_6), K7(GLFW_KEY_7), K8(GLFW_KEY_8), K9(GLFW_KEY_9), K0(GLFW_KEY_0),
		GRAVE_ACCENT(GLFW_KEY_GRAVE_ACCENT),

		// NUMPAD
		N1(GLFW_KEY_KP_1), N2(GLFW_KEY_KP_2), N3(GLFW_KEY_KP_3), N4(GLFW_KEY_KP_4), N5(GLFW_KEY_KP_5),
		N6(GLFW_KEY_KP_6), N7(GLFW_KEY_KP_7), N8(GLFW_KEY_KP_8), N9(GLFW_KEY_KP_9), N0(GLFW_KEY_KP_0),
		
		// LEFT NOTATIONS
		K_MINUS(GLFW_KEY_MINUS), K_PLUS(GLFW_KEY_EQUAL), L_BRACKET(GLFW_KEY_LEFT_BRACKET), 
		R_BRACKET(GLFW_KEY_RIGHT_BRACKET), BACKSPACE(GLFW_KEY_BACKSPACE), SEMI_COLON(GLFW_KEY_SEMICOLON),
		APOSTROPHE(GLFW_KEY_APOSTROPHE), FORWARD_SLASH(GLFW_KEY_SLASH), BACKWARD_SLASH(GLFW_KEY_BACKSLASH),
		COMMA(GLFW_KEY_COMMA), PERIOD(GLFW_KEY_PERIOD),

		// NUMPAD NOTATIONS
		DECIMAL(GLFW_KEY_KP_DECIMAL), DIVIDE(GLFW_KEY_KP_DIVIDE), MULTIPLY(GLFW_KEY_KP_MULTIPLY),
		SUBTRACT(GLFW_KEY_KP_SUBTRACT), ADD(GLFW_KEY_KP_ADD)
	{

		switch (platform)
		{
		case Lafez::GraphicsAPI::None: {
			LZ_ENGINE_INFO("KEYCODE SET INITIALIZED WITH ERROR");
			break;
		}
		case Lafez::GraphicsAPI::GL: {
			LZ_ENGINE_INFO("GLFW KEYCODE SET INITIALIZED");
			break;
		}
		case Lafez::GraphicsAPI::VK: {
			LZ_ENGINE_INFO("GLFW KEYCODE SET INITIALIZED");
			break;
		}

		#ifdef __LZ_WIN
			case Lafez::GraphicsAPI::DX: {
				LZ_ENGINE_INFO("WIN32 KEYCODE SET INITIALIZED WITH ERROR");
				break;
			}
		#endif

		default:
			break;
		}
	}
}