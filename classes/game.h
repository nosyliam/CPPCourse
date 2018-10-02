#include <media.h>

class Game : public Media {
 public:
  Game() {};

  MediaType Type();
  void Display();
  void Fill();
  
  std::string Publisher();
  int Rating();
  
 private:
  std::string m_publisher;
  int m_rating = 0;
};
