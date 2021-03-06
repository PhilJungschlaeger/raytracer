/*shape.cpp 
Feel free to shape yourself.
*/
#include "shape.hpp"
//KONSTRUTOREN----------------------------------------------------------------------
  //Default
	Shape::Shape() :
	m_name {"Shape"}, 
	m_mat {}
	{ 
		std::cout << "Shape-Construction" << m_name << std::endl;
	}

	//Custom
	/*
	Shape::Shape(std::string const& name, Material const& mat) : 
	m_name {name},
	m_mat {std::make_shared<Material> mat}  
	{
		std::cout <<":Shape-Construction: " << m_name << std::endl;
	}*/

	//Custom
	Shape::Shape(std::string const& name, std::shared_ptr<Material> mat) : 
	m_name {name},
	m_mat {mat}
	{
		std::cout <<":Shape-Construction: " << m_name << std::endl;
	}

	// Destructor 
	Shape::~Shape() 
	{
	  std::cout << "Shape-Destruction: " << m_name << std::endl;
	}

//GETTER----------------------------------------------------------------------
	std::string Shape::name() const 
	{
	  return m_name;
	}
	std::shared_ptr<Material> Shape::material() const 
	{
	  return m_mat; 
	}

//FUNKTIONEN---------------------------------------------------------------------
	// print 1
	std::ostream& Shape::print(std::ostream& os) const 
	{
	  os << "Name: " << m_name << "\n" 

	  << "Material: (" << m_mat<< std::endl;
	  return os;
	}

	// print 2
	std::ostream& operator << (std::ostream& os, Shape const& s) 
	{
	  return s.print(os);
	}
	/*
	bool Shape::transf() const
	{
		return m_transf;
	}

	glm::vec3 const& Shape::transl()const
	{
		return m_transl;
	}
*/
	