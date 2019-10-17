  
#ifndef ZEDBOARD_H
#define ZEDBOARD_H

class ZedBoard {
   public:
	void RegisterWrite(int, int);
	int RegisterRead(int);
	void Write1Led(int, int);
	void WriteAllLeds(int);
	int PushButtonGet();
	ZedBoard();
	~ZedBoard();  

   private:
	char *pBase;
	int fd;
};

#endif
