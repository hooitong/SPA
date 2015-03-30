using namespace std;

class DivisionByZeroException{
		public:
				DivisionByZeroException()
						: message("Division by zero error!"){}
				const char * what() const{ return message;}
		private:
				const char * message;
};