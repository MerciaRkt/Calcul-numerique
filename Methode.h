#include <vector>

class Methode 
{
    private :
        std::vector <std::string> T ;
    public :
        void entrer (std :: string fonction) ;
        double  calcul (std::string fonction, double x);
        double dichotomie( ) ;
        double newton () ;
        double f (double x) ;
        double derive(double x) ;
} ;
