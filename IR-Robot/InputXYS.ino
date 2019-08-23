#ifndef InputXYS_h
#define InputXYS_h 

class InputXYS {
	private:
	public:
		int x, y, s;
		InputXYS(int x_arg, int y_arg, int s_arg) { 
			x = x_arg;
			y = y_arg;
			s = s_arg;
		};
		InputXYS() { 
		};
		int getX();
		int getY();
		int getS();
		void setX(int x_arg);
		void setY(int y_arg);
		void setS(int s_arg);
}; 
	int InputXYS::getX() {
		return x;
	}

	int InputXYS::getY() {
		return y;
	}

	int InputXYS::getS() {
		return s;
	}
	void InputXYS::setX(int x_arg) {
		x = x_arg;
	}

	void InputXYS::setY(int y_arg) {
		y = y_arg;
	}

	void InputXYS::setS(int s_arg) {
		s = s_arg;
	}



#endif