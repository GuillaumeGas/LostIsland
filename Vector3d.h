/**
* \file Vector3D.h
* \author Spl!nt
* \date 20 juin 2008
* \brief Vecteur contenant trois nombres à double précision. Cette classe peut être très utile pour la 3D puisqu'elle contient des méthodes permettant une utilisation simple des calculs couramment utilisés et souvent pénible à effectuer.
*/
#ifndef Vector3D_H
#define Vector3D_H

/**
* \brief Vecteur contenant trois nombres à double précision. Cette classe peut être très utile pour la 3D puisqu'elle contient des méthodes permettant une utilisation simple des calculs couramment utilisés et souvent pénible à effectuer.
*/
class Vector3D{

public:
    double X;
    double Y;
    double Z;

    /**
    * \brief Constructeur par défaut - Construit un nouveau vecteur nul
    * \return Instance nouvellement allouée d'un objet de type Vector3D
    */
    Vector3D();
    /**
    * \brief Construit un nouveau vecteur où les trois getCompos()antes sont fixées par les valeurs passées en paramètre
    * \param x,y,z Valeurs fixées pour les trois getCompos()antes du vecteur
    * \return Instance nouvellement allouée d'un objet de type Vector3D
    */
    Vector3D(double x,double y,double z);
    /**
    * \brief Constructeur de recopie
    * \param v Vector3D à recopier
    * \return Instance nouvellement allouée d'un objet de type Vector3D
    */
    Vector3D(const Vector3D & v);
    Vector3D(const Vector3D & from,const Vector3D & to);

    Vector3D & operator= (const Vector3D & v);

    Vector3D & operator+= (const Vector3D & v);
    Vector3D operator+ (const Vector3D & v) const;

    Vector3D & operator-= (const Vector3D & v);
    Vector3D operator- (const Vector3D & v) const;

    Vector3D & operator*= (const double a);
    Vector3D operator* (const double a)const;
    friend Vector3D operator* (const double a,const Vector3D & v);

    Vector3D & operator/= (const double a);
    Vector3D operator/ (const double a)const;

    /**
    *\brief Produit vectoriel, dont la valeur sera donc (\f$y*vec.z-z*vec.y,z*vec.w-w*vec.z,w*vec.x-x*vec.w,x*vec.y-y*vec.x\f$)
    *\param v Vecteur avec lequel opéré
    *\return Le vecteur résultat du produit vectoriel
    */
    Vector3D crossProduct(const Vector3D & v)const;
    /**
    *\brief Permet d'obtenir la norme du vecteur, dont la valeur sera donc (\f$\sqrt{x^2+y^2+w^2+z^2}\f$)
    *\return Norme du vecteur
    */
    double length()const;

    /**
    *\brief Permet de normaliser le vecteur, dont la valeur sera donc (\f$\frac{x}{norme},\frac{y}{norme},\frac{z}{norme},\frac{w}{norme}\f$)
    *\return Le vecteur normalisé
    *\see length()
    */
    Vector3D & normalize();
};

#endif //Vector3D_H
