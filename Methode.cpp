#include <iostream>
#include <cmath>
#include "Methode.h"
#include <vector>
#include <string>


void Methode :: entrer (std :: string fonction)
{
    std ::string actuel ;
    int i ,j , puissance , compteur ;

    for (i = 0 ;i < fonction.size(); i++)
    {
        if (fonction[i] == ' ')
        {
            continue;
        }
        if (fonction[i] >= '0' && fonction[i] <= '9')
        {
            actuel= actuel + fonction[i] ;

            if (i+1 < fonction.size() && fonction[i+1] == 'x')
            {
                actuel = actuel + '*';
            }
        }
        else if(fonction[i] == 'x')
        {
            if (i+2 < fonction.size()&& fonction[i+1] == '^' && fonction[i+2] >= '0' && fonction[i+2] <= '9')
            {
                puissance = fonction[i+2] - '0' ;
                for ( j = 0 ; j < puissance ; j++)
                {
                    if (j != puissance - 1)
                    {
                        actuel = actuel + "x*" ;
                    }
                    else
                    {
                        actuel = actuel + 'x' ;
                    }
                }
                i = i+2 ;
            }
            else
            {
                actuel = actuel + "x";
            }
        }
        else
        {
            actuel = actuel + fonction[i] ;
        }
    }

    fonction = actuel ;
    actuel = "" ;


    i =0 ;
    while (i < fonction.size())
    {
        if (fonction[i] == '(')
        {
            actuel = "";
            compteur = 1;
            actuel = actuel + fonction[i];
            i = i +1;
            
            while (i < fonction.size() && compteur > 0)
            {
                if (fonction[i] == '(') 
                {
                    compteur++;
                }
                if (fonction[i] == ')') 
                {
                    compteur--;
                }
                actuel = actuel + fonction[i];
                i = i +1;
            }

            T.push_back(actuel);
        }
        else if (fonction[i] == '/')
        {
            T.push_back("/");
            i++;
        }
        else
        {
            actuel = "";
            while (i < fonction.size() && fonction[i] != '(' && fonction[i] != '/')
            {
                actuel = actuel + fonction[i];
                i = i +1 ;
            }

            if (actuel.size() != 0)
            {
                T.push_back(actuel);
            }
        }
    }

    for (int k = 0; k < T.size(); k++)
    {
        std::cout << "T[" << k << "] = " << T[k] << std::endl;
    }
}

double Methode :: calcul(std::string fonction, double x)
{
    int i ,j , coef ,nombreX ,signe;
    double resultat ,resultat1 ;
    resultat1 = 0 ;
    std ::string contenu , actuel ;
    std :: vector <std::string> temp ; 

    actuel = "";

    if (fonction[0] == '(')
    {
        fonction = fonction.substr(1, fonction.size()-2);
    }

    for ( i = 0 ; i < fonction.size() ;i++)
    {
        if (fonction[i] != '+' && fonction[i] != '-')
        {
            actuel = actuel + fonction[i] ;
        }
        else
        {
            if (actuel.size() != 0)
            {
                temp.push_back(actuel);
            }

            actuel = "";
            actuel = actuel + fonction[i];
        }
    }

    if (actuel.size() != 0)
    {
        temp.push_back(actuel);
    }

    for ( i = 0 ; i < temp.size() ;i++)
    {
        coef =0 ;
        nombreX=0;
        contenu = temp[i] ;

        for (j = 0 ; j < contenu.size() ; j++)
        {
            if (contenu[j]>= '0' && contenu[j] <='9')
            {
                coef = coef *10 + (contenu[j] - '0' );
            }
            else if (contenu[j] == 'x')
            {
                break;
            }
        }

        if (coef == 0 && contenu.find('x') != std::string::npos)
        {
            coef = 1 ;
        }

        for (j=0 ; j<contenu.size() ;j++)
        {
            if (contenu[j] == 'x')
            {
                nombreX ++;
            }
        }

        resultat = coef ;
        for (j =0 ;j<nombreX ;j++)
        {
            resultat = resultat * x ;
        }

        if (contenu[0] == '-')
        {
            signe = -1 ;
        }
        else
        {
            signe = 1;
        }

        resultat = signe * resultat;
        resultat1 = resultat1 + resultat ;
    }

    return resultat1 ;
}

double Methode :: f (double x)
{
    int i;
    double resultat , courant , denominateur;

    resultat = 0;
    resultat = calcul(T[0], x);

    for (i = 1; i < T.size(); i++)
    {
        if (T[i] == "/")
        {
            denominateur = calcul(T[i+1], x);

            resultat = resultat / denominateur;
            i++; 
        }
        else
        {
            courant = calcul(T[i], x);
            resultat = resultat + courant;
        }
    }

    return (resultat);
}

/*double Methode :: f (double x )
{
    return (3*x*x - 7) ;
}*/

double Methode :: derive (double x)
{
    return (6*x) ;
}

double Methode :: newton()
{
    double xn , xnP1 , val , epsilon ;
    int i = 0 , d;
    val= 1 ;
    epsilon = 0.000001;
    
    do 
    {
        xn = val;
        d = derive(xn);
        if (fabs(d) < 0.0000001)
        {
            std :: cout << "derivee nulle" << std :: endl ;
            break;
        }
        xnP1 = (xn - (f(xn) / derive(xn)));
        //std ::cout << "xn = " << xn << "f(xn) = " << f(xn) << "derive(xn) == " << derive(xn) << std::endl ;
        val = xnP1 ;
        i++ ;
    }
    while (fabs(xnP1 - xn) > epsilon) ;

    std :: cout << "Nombre d'iteration = " << i << std ::endl ;
    return(val) ;
}


double Methode :: dichotomie()
{
    double a , b ,centre , epsilon ;
    int i = 0; 
    a = 1 ;
    b = 3 ;
    epsilon = 0.000001;

    if (f(a) * f(b) < 0)
    {
        while ( b - a > epsilon )
        {
            centre = (a + b )/ 2 ;

            //std :: cout << "a = " << a << " f(a)== " << f(a) <<  " b= " << b << " f(b)== "<<f(b) << " centre== " << centre << " f(centre)== " << f(centre) << std:: endl;
            if (f(a) * f(centre) <= 0) 
            {
                b = centre ;
            }
            else
            {
                a = centre ;        
            }
            i++ ;
        }
        std :: cout << "Nombre d'iteration = " << i << std ::endl ;
    }

    return(centre) ;
}


