#ifndef WIIMOTEACCEL_H
#define WIIMOTEACCEL_H

class WiimoteAccel {
   public:
      void Listen();
      virtual void AccelerationEvent(int, int);
      WiimoteAccel(); 
      ~WiimoteAccel();  
 
   private:
      int fd;
};

#endif
