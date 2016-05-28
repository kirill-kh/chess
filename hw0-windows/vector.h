#pragma once

template<typename T>
class vector
{
public:
	T x;
	T y;
	T z;
public:
	vector(void);
	vector(T x, T y, T z);
	vector(const vector<T> & Original);
	~vector(void);

	vector<T> & operator = (const vector<T> & Original);
	vector<T> & operator = (T Num);
	vector<T> operator * (float Num);
	vector<T> & operator *= (float Num);
	vector<T> operator - ();
	vector<T> operator - (const vector<T> & Sec);

	T * VecInMass();
	float mod(const vector<T> & vec);
	vector<T> vecmul(const vector<T> & vec1, const vector<T> & vec2);

};


template<typename T>
class vector2d
{
public:
	T x;
	T y;
public:
	vector2d(void);
	vector2d(T x, T y);
	vector2d(const vector2d<T> & Original);
	~vector2d(void);

	vector2d<T> & operator = (const vector2d<T> & Original);
	vector2d<T> & operator = (T Num);
	vector2d<T> operator * (float Num);
	vector2d<T> & operator *= (float Num);
	vector2d<T> operator - ();

	T * VecInMass();

};


//Constructors
template <typename T>
vector<T>::vector(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
template <typename T>
vector<T>::vector(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
template <typename T>
vector<T>::vector(const vector<T> & Original)
{
	this->x = Original.x;
	this->y = Original.y;
	this->z = Original.z;
}
//Destructor
template <typename T>
vector<T>::~vector(void)
{
}
//Operators
template <typename T>
vector<T> & vector<T>::operator = (const vector<T> & Original)
{
	this->x = Original.x;
	this->y = Original.y;
	this->z = Original.z;
	return (*this);
}
template <typename T>
vector<T> & vector<T>::operator = (T Num)
{
	this->x = Num;
	this->y = Num;
	this->z = Num;
	return (*this);
}
template <typename T>
vector<T> vector<T>::operator * (float Num)
{
	vector<T> A(this->x * Num,this->y * Num,this->z * Num);
	return A;
}
template <typename T>
vector<T> & vector<T>::operator *= (float Num)
{
	(*this) = (*this) * Num;
	return (*this);
}
template <typename T>
vector<T> vector<T>::operator - ()
{
	vector<T> A(-x,-y,-z);
	return A;
}
template <typename T>
vector<T> vector<T>::operator - (const vector<T> & Sec)
{
	vector<T> A(this->x- Sec.x,this->y-Sec.y,this->z-Sec.z);
	return A;
}

//funcions
template <typename T>
T * vector<T>::VecInMass()
{
	T * Mass = new T [3];
	Mass[0] = this->x;
	Mass[1] = this->y;
	Mass[2] = this->z;
	return Mass;
}
template <typename T>
vector<T> vector<T>::vecmul(const vector<T> & vec1, const vector<T> & vec2)
{
	vector<T> A(vec1.y*vec2.z-vec1.z*vec2.y,vec1.z*vec2.x-vec1.x*vec2.z,vec1.x*vec2.y-vec1.y*vec2.x);
	return A;
}


template <typename T>
float vector<T>::mod(const vector<T> & vec)
{
	return sqrt((vec.x-x)*(vec.x-x)+(vec.y-y)*(vec.y-y)+(vec.z-z)*(vec.z-z));
}









template <typename T>
vector2d<T>::vector2d(void)
{
	this->x = 0;
	this->y = 0;
}
template <typename T>
vector2d<T>::vector2d(T x, T y)
{
	this->x = x;
	this->y = y;
}
template <typename T>
vector2d<T>::vector2d(const vector2d<T> & Original)
{
	this->x = Original.x;
	this->y = Original.y;
}
//Destructor
template <typename T>
vector2d<T>::~vector2d(void)
{
}
//Operators
template <typename T>
vector2d<T> & vector2d<T>::operator = (const vector2d<T> & Original)
{
	this->x = Original.x;
	this->y = Original.y;
	return (*this);
}
template <typename T>
vector2d<T> & vector2d<T>::operator = (T Num)
{
	this->x = Num;
	this->y = Num;
	return (*this);
}
template <typename T>
vector2d<T> vector2d<T>::operator * (float Num)
{
	vector<T> A(this->x * Num,this->y * Num);
	return A;
}
template <typename T>
vector2d<T> & vector2d<T>::operator *= (float Num)
{
	(*this) = (*this) * Num;
	return (*this);
}
template <typename T>
vector2d<T> vector2d<T>::operator - ()
{
	vector2d<T> A(-x,-y);
	return A;
}

//functions
template <typename T>
T * vector2d<T>::VecInMass()
{
	T * Mass = new T [2];
	Mass[0] = this->x;
	Mass[1] = this->y;
	return Mass;
}






