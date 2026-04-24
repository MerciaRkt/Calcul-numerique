#include <vector>

class Methode 
{
    private :
        std::vector <std::string> T ;
    public :
        //void Methode :: parenthese ( std::string fonction) ;
        void entrer (std :: string fonction) ;
        void df ( std :: string fonction) ;
        double  calcul (double x);
        double dichotomie( ) ;
        double newton () ;
        double f (double x) ;
        double derive(double x) ;
} ;