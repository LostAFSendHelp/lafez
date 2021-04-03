#include <exports/lafezlib_export.h>
#include "Foundation.hpp"

namespace Lafez {
	class LAFEZLIB Key {
	public:
		static void startUp(FoundationPlatform platform);
		static void shutDown();

		static Key* getInstance();

		// ALPHABETS
		const int A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
		// FUNCTIONS
		const int F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12;
		// ARROWS
		const int UP, DOWN, LEFT, RIGHT;
		// CONTROLS
		const int ESCAPE, TAB, L_SHIFT, R_SHIFT, L_CTRL, R_CTRL, L_ALT, R_ALT, L_ENTER, R_ENTER;
		// NUMBERS
		const int K1, K2, K3, K4, K5, K6, K7, K8, K9, K0, GRAVE_ACCENT;
		// NUMPAD
		const int N1, N2, N3, N4, N5, N6, N7, N8, N9, N0;
		// LEFT NOTATIONS
		const int K_MINUS, K_PLUS, L_BRACKET, R_BRACKET, BACKSPACE, SEMI_COLON, APOSTROPHE;
		// LEFT NOTATIONS
		const int FORWARD_SLASH, BACKWARD_SLASH, COMMA, PERIOD;
		// NUMPAD NOTATIONS
		const int DECIMAL, DIVIDE, MULTIPLY, SUBTRACT, ADD;
	private:
		Key(FoundationPlatform platform);
		~Key() = default;

		static Key* sShared;
	};
};