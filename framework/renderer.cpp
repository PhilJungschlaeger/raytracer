/*renderer.cpp 
Feel free to render!
*/
#include "renderer.hpp"
#include <glm/glm.hpp>

//KONSTRUTOREN----------------------------------------------------------------------
   /*Custom 1 
  ######################################
  Setzt Renderer Custom mit gewünschter
  Szene, Resolution und Output auf. 
  Nun kann gerendert werden */
  Renderer::Renderer(Scene const& scene, unsigned int width, unsigned int height, std::string const& ofile): 
    m_scene(scene),
    m_width(width), 
    m_height(height), 
    m_colorbuffer(width*height, Color(0.0, 0.0, 0.0)), 
    m_outfile(ofile),
    m_ppm(m_width, m_height),
    m_processing(false)
    {}

//FUNKTIONEN------------------------------------------------------------------------
  /*Fkt: render
  ######################################
  Organisiert die Pixel Farbgebung! */
  void Renderer::render()
  {
    m_processing=true;

    float distance = 200; // to be set ?
    float height = (-float(m_height)/2); 

    for (unsigned y = 0; y < m_height; ++y) {     //Horizontal
      float width = (-float(m_width)/2);
      
      for (unsigned x = 0; x < m_width; ++x) {    //Vertikal
        Pixel p(x,y);

        //For Preview
        p.color=Color(1.0,1.0,1.0);
        write(p); 

        //Erzeuge Ray
        Ray rayman {{0,0,0}, glm::normalize(glm::vec3(width, height, distance))};
        p.color=givacolor(rayman);

        write(p);
        width++;
      }
      height++;
    }
    m_ppm.save(m_outfile);
    m_processing=false;
  }

   /*Fkt: write
  ######################################
  Schreibt einfach schön herum
  (ppmwriter)! Hab ich nicht geschrieben */
  void Renderer::write(Pixel const& p)
  {
    // flip pixels, suck dick , because of opengl glDrawPixels
    size_t buf_pos = (m_width*p.y + p.x);
    if (buf_pos >= m_colorbuffer.size() || (int)buf_pos < 0) 
    {
      std::cerr << "Fatal Error Renderer::write(Pixel p) : "
        << "pixel out of ppm_ : "
        << (int)p.x << "," << (int)p.y
        << std::endl;
    }else 
    {
      m_colorbuffer[buf_pos] = p.color;
    }
    m_ppm.write(p);
  }

   /*Fkt: givacolor
  ######################################
  Ermittelt die Fabrbe! */
  Color Renderer::givacolor(Ray const& ray)
  {
    Hit Hitze = ohit(ray);

    if(Hitze.m_hit==true) //Treffer?
    {
       Color clr= //+=I_a*k_a
       (m_scene.m_ambient) * (Hitze.m_shape->material().ka); 
      
      //Überprüfe nun alle direkten Lichtwege
      for(auto& light : m_scene.m_lights) 
      {
        Ray raylight
        {
          Hitze.m_point+(glm::normalize(Hitze.m_normal)*0.0001f), //nicht selbst Treffen
          glm::normalize(light->m_point-Hitze.m_point)
        };       

        int distance= glm::length(Hitze.m_point-light->m_point);
        Hit LightHitze = ohit(raylight);
        
        if (LightHitze.m_distance>distance) //Licht?
        {
          float faktor=
          (
            glm::dot(glm::normalize(Hitze.m_normal) , raylight.m_direction)
          );

          if (faktor<0)
          {
            faktor=0;
          }

          clr+= 
          light->m_color 
          *Hitze.m_shape->material().kd 
          *faktor; 
        }//else{Schatten
      }
      return clr;   
    }//else{Hit=false:
    return m_scene.m_ambient; //Ambient Light?
  }    
        


   /*Fkt: ohit
  ######################################
  Gibt das durch einen Ray als erstes
  getroffene Objekt mit DATA zurück! */
  Hit Renderer::ohit(Ray const& ray) const
  {
    Hit hit;
    Hit temphit;
    for ( auto &i : m_scene.m_shapes )
    {
      temphit= i->intersect(ray);
      if(temphit.m_distance<hit.m_distance)
      {
        hit =  temphit;
      }
    } 
    return hit;
  }


