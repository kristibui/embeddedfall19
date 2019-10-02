#ifndef WIIMOTEBTNS_H
#define WIIMOTEBTNS_H

class WiimoteBtns {
   public:
      void Listen();
      void ButtonEvent(int, int);
      WiimoteBtns(); 
      ~WiimoteBtns();  
 
   private:
      int fd;
};

#endif
