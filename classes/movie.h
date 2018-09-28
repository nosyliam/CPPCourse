#include <media.h>

class Movie : public Media {
 public:
  Movie() {};

  MediaType Type();
  void Display();
  void Fill();
  
  std::string Director();
  int Duration();
  int Rating();
  
 private:
  std::string m_director;
  int m_duration = 0;
  int m_rating = 0;
};
