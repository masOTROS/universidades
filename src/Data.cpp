#include "Data.h"

//--------------------------------------------------------------
void Data::setup(){
    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
    // Load a CSV File.
    if(csv.load("input.csv")) {
        ofLog() << "Get all possible RAMAS";
        for(int i = 0; i < csv.getNumRows(); i++) {
            string nombreRama = csv[i][2];
            int compare = -1;
            for(int j = 0; j<Ramas.size(); j++){
                compare = nombreRama.compare(Ramas[j].nombre);
                if(!compare){
                    break;
                }
            }
            if(compare){
                Rama newRama;
                newRama.nombre=nombreRama;
                Ramas.push_back(newRama);
            }
        }
        for(int i = 0; i < Ramas.size(); i++){
            ofLog() << Ramas[i].nombre;
        }
        
        ofLog() << "Get all possible PROVINCIAS";
        for(int i = 0; i < csv.getNumRows(); i++) {
            string nombreProvincia = csv[i][1];
            int compare = -1;
            for(int j = 0; j<Provincias.size(); j++){
                compare = nombreProvincia.compare(Provincias[j].nombre);
                if(!compare){
                    break;
                }
            }
            if(compare){
                Provincia newProvincia;
                newProvincia.nombre=nombreProvincia;
                Provincias.push_back(newProvincia);
            }
        }
        for(int i = 0; i < Provincias.size(); i++){
            ofLog() << Provincias[i].nombre;
        }
        
        ofLog() << "Get all possible UNIVERSIDADES";
        for(int i = 0; i < csv.getNumRows(); i++) {
            string nombreUniversidad = csv[i][0];
            int compare = -1;
            for(int j = 0; j<Universidades.size(); j++){
                compare = nombreUniversidad.compare(Universidades[j].nombre);
                if(!compare){
                    break;
                }
            }
            if(compare){
                Universidad newUniversidad;
                newUniversidad.nombre=nombreUniversidad;
                Universidades.push_back(newUniversidad);
            }
        }
        for(int i = 0; i < Universidades.size(); i++){
            ofLog() << Universidades[i].nombre;
        }
        
        for(int i = 0; i < csv.getNumRows(); i++) {
            string nombreUniversidad = csv[i][0];
            string nombreProvincia = csv[i][1];
            string nombreRama = csv[i][2];
            Rama * rama = NULL;
            for(int j = 0; j<Ramas.size(); j++){
                if(!nombreRama.compare(Ramas[j].nombre)){
                    rama = &Ramas[j];
                    break;
                }
            }
            Provincia * provincia = NULL;
            for(int j = 0; j<Provincias.size(); j++){
                if(!nombreProvincia.compare(Provincias[j].nombre)){
                    provincia = &Provincias[j];
                    break;
                }
            }
            Universidad * universidad = NULL;
            for(int j = 0; j<Universidades.size(); j++){
                if(!nombreUniversidad.compare(Universidades[j].nombre)){
                    universidad = &Universidades[j];
                    break;
                }
            }
            
            
            if ( std::find(rama->provincias.begin(), rama->provincias.end(), provincia) == rama->provincias.end() )
                rama->provincias.push_back(provincia);
            
            if ( std::find(rama->universidades.begin(), rama->universidades.end(), universidad) == rama->universidades.end() )
                rama->universidades.push_back(universidad);
            
            if ( std::find(provincia->ramas.begin(), provincia->ramas.end(), rama) == provincia->ramas.end() )
                provincia->ramas.push_back(rama);
            
            if ( std::find(provincia->universidades.begin(), provincia->universidades.end(), universidad) == provincia->universidades.end() )
                provincia->universidades.push_back(universidad);
            
            if ( std::find(universidad->ramas.begin(), universidad->ramas.end(), rama) == universidad->ramas.end() )
                universidad->ramas.push_back(rama);
            
            if ( std::find(universidad->provincias.begin(), universidad->provincias.end(), provincia) == universidad->provincias.end() )
                universidad->provincias.push_back(provincia);
            
        }
        ofLog() << "Print all the deita";
        for(int i = 0; i < Universidades.size(); i++){
            ofLog() << "Universidad: " << Universidades[i].nombre;
            ofLog() << " en las provincias ";
            for(int j = 0; j < Universidades[i].provincias.size(); j++)
                ofLog() << Universidades[i].provincias[j]->nombre;
            ofLog() << " con las ramas ";
            for(int j = 0; j < Universidades[i].ramas.size(); j++)
                ofLog() << Universidades[i].ramas[j]->nombre;
        }
    }
}
    
//--------------------------------------------------------------
void Data::resetFiltered(){
    filteredRamas.clear();
    for(int i=0; i<Ramas.size(); i++){
        filteredRamas.push_back(&Ramas[i]);
    }
    
    filteredProvincias.clear();
    for(int i=0; i<Provincias.size(); i++){
        filteredProvincias.push_back(&Provincias[i]);
    }
    
    filteredUniversidades.clear();
    for(int i=0; i<Universidades.size(); i++){
        filteredUniversidades.push_back(&Universidades[i]);
    }
}

//--------------------------------------------------------------
void Data::applyRamaFilter(Rama * r){
    filteredRamas.clear();
    filteredRamas.push_back(r);
    
    for (vector<Provincia *>::iterator it=filteredProvincias.begin(); it!=filteredProvincias.end(); /*it++*/){
        bool valid = false;
        for(int i=0; i<(*it)->ramas.size(); i++){
            Rama * rr = (*it)->ramas[i];
            valid |= (r == rr);
        }
        if(!valid)
            it = filteredProvincias.erase(it);
        else
            ++it;
    }
    
    for (vector<Universidad *>::iterator it=filteredUniversidades.begin(); it!=filteredUniversidades.end(); /*it++*/){
        bool valid = false;
        for(int i=0; i<(*it)->ramas.size(); i++){
            Rama * rr = (*it)->ramas[i];
            valid |= (r == rr);
        }
        if(!valid)
            it = filteredUniversidades.erase(it);
        else
            ++it;
    }
}

//--------------------------------------------------------------
void Data::applyProvinciaFilter(Provincia * p){
    filteredProvincias.clear();
    filteredProvincias.push_back(p);
    
    for (vector<Rama *>::iterator it=filteredRamas.begin(); it!=filteredRamas.end(); /*it++*/){
        bool valid = false;
        for(int i=0; i<(*it)->provincias.size(); i++){
            Provincia * pp = (*it)->provincias[i];
            valid |= (p == pp);
        }
        if(!valid)
            it = filteredRamas.erase(it);
        else
            ++it;
    }
    
    for (vector<Universidad *>::iterator it=filteredUniversidades.begin(); it!=filteredUniversidades.end(); /*it++*/){
        bool valid = false;
        for(int i=0; i<(*it)->provincias.size(); i++){
            Provincia * pp = (*it)->provincias[i];
            valid |= (p == pp);
        }
        if(!valid)
            it = filteredUniversidades.erase(it);
        else
            ++it;
    }
}


//--------------------------------------------------------------
void Data::applyUniversidadFilter(Universidad * u){
    filteredUniversidades.clear();
    filteredUniversidades.push_back(u);
    
    for (vector<Rama *>::iterator it=filteredRamas.begin(); it!=filteredRamas.end(); /*it++*/){
        bool valid = false;
        for(int i=0; i<(*it)->universidades.size(); i++){
            Universidad * uu = (*it)->universidades[i];
            valid |= (u == uu);
        }
        if(!valid)
            it = filteredRamas.erase(it);
        else
            ++it;
    }
    
    for (vector<Provincia *>::iterator it=filteredProvincias.begin(); it!=filteredProvincias.end(); /*it++*/){
        bool valid = false;
        for(int i=0; i<(*it)->universidades.size(); i++){
            Universidad * uu = (*it)->universidades[i];
            valid |= (u == uu);
        }
        if(!valid)
            it = filteredProvincias.erase(it);
        else
            ++it;
    }
}

//--------------------------------------------------------------
void Data::printFiltered(){
    for(int i=0; i<filteredRamas.size(); i++)
        cout<<filteredRamas[i]->nombre<<endl;
    for(int i=0; i<filteredProvincias.size(); i++)
        cout<<filteredProvincias[i]->nombre<<endl;
    for(int i=0; i<filteredUniversidades.size(); i++)
        cout<<filteredUniversidades[i]->nombre<<endl;
}