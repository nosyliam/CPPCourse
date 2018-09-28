#include <media.h>

class Music : public Media {
 public:
  Music() {};

  MediaType Type();
  void Display();
  void Fill();
  
  std::string Publisher();
  std::string Artist();
  int Duration();
  
 private:
  std::string m_publisher;
  std::string m_artist;
  int m_duration = 0;
};
