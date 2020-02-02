/**
  *@file Chainage.cpp
  *@author BA MATRAF Abrahim Fekri , ALKHAFAJI Husamu Aldeen
  *@brief : un algorithme de tri par fusion multiple de monotonies.

**/
#include <iostream>
using namespace std;

/***************constants et structs ******************/

typedef string DATATYPE;

// Chaînage 

typedef struct _datum {
  DATATYPE valeur ;
  _datum * suiv ;
} data ;

typedef data * p_data ;


// tableau des chainages

typedef struct _datallst {
  int capa ;
  int nbmono ;
  p_data * monotonies ;
} datalistes ;



/******************************/

/***Les fonctions et procédures de chainage***/

/**
 *@Role: procédure qui affiche tous les maillons du chainage
 *@param : la tete du chainage
 *@PRE:
 *@POST:
*/
void aff(p_data chain){
  
  while (chain != nullptr){
    cout << (chain->valeur) << " ";
    chain = (chain->suiv);
  }
  cout << "" <<endl;  // passer a la prochain ligne a la fin d'affichage

}
/**
 *@Role: une fonction qui cree un nouveau maillon et le ajouter 
    a la tete  du chainage.
 *@param:   une valeur (uneval) et la tete du chainage (chain).
 *@retourner: retourner la nouvelle tete du chainage
 *@PRE: chain doit etre alloué
 *@POST:
*/
p_data ajoutDevant(DATATYPE uneval , p_data chain){
  p_data tmp;
  tmp = new data;
  (*tmp).valeur = uneval;
  (*tmp).suiv = chain;
  chain = tmp;

  return chain;

}

/**
 *@Role:une fonction qui lit une succession de valeurs et les 
   mémorise (dans le même ordre) dans un chaînage terminé par nullptr,
   la saisie se termine à la première occurrence d’une valeur égale à sentinelle.
 
 *@retourner: la tete du chainage
 *@param: la valeur qui termine la  saisir 
 *@PRE:
 *@POST:

**/
p_data saisieBorne(DATATYPE sent){
  p_data tete = nullptr;
  p_data queue;

  DATATYPE candidate;
  cout << "entrez la valeur de premiere maillon1 " << endl;
  cin >> candidate;
  //cas de premier maillon1
  if(candidate != sent){
    tete = new data;
    queue = tete;
    (*queue).valeur = candidate;
    (*queue).suiv = nullptr;
  }else{
    return tete;
  }

  //sasie de la valeur de la deuxieme maillon1
  cout << "entrez la valeur de maillon1 suivante" << endl;
  cin >> candidate;
  //tous les maillon1 apres la premier
  while(candidate != sent){
      (*queue).suiv = new data;
      queue = (*queue).suiv;
      (*queue).valeur = candidate;
      (*queue).suiv = nullptr;
      cout << "entrez la valeur de maillon1 suivante" << endl;
      cin >> candidate;

  }


  return tete;

}

/**
 *@Role: une fonction qui lit  une succession de nb valeurs et 
   les mémorise dans un chaînage terminé par nullptr.
 
 *@retourner: la tete du chainage.
 *@param: la nombre de la valeur à mémoriser.
 *@PRE:
 *@POST:
*/
p_data saisieNombre(int nb){
  p_data tete;
  p_data queue;

  //cas de chainage d'une element quand nb = 1
  tete = new data;
  cout << "entrez la valeur de premiere maillon1 " << endl;
  cin >> (*tete).valeur;
  (*tete).suiv = nullptr;
  queue = tete;

  // cas de chainage quand elemets >= 2
  for(int i = 2; i <= nb; i++){

    (*queue).suiv = new data;
    queue = (*queue).suiv;
    cout << "entrez la valeur de maillon1 suivante " << endl;
    cin >> (*queue).valeur;
    (*queue).suiv = nullptr;

  }

  return tete;

}



/**
 *@Role:une procédure qui ajoute le chainage (mono) à la fin 
    du chainage (chain)
 *@param: les tetes de deux chainages mono et chain   
 *@PRE: mono ne doit etre vide,et chain doit avoir au moins
      un seul maillon ou égal à nullptr

*/
void addChain( p_data mono ,p_data & chain ){
  
  p_data queueDeChain;
  queueDeChain = chain;

  if(chain == nullptr){
    chain = mono;
  }else{

    //boucle pour que la pointeur queueDeChain 
    //pointe vers la dernier élément
    while((queueDeChain->suiv) != nullptr){
    queueDeChain = (queueDeChain->suiv);
    }
  
    //ajoute mono à la fin du chainage (chain)
    (queueDeChain->suiv) = mono;
  }

}

/**
 *@Role:une fonction qui fusionne deux chaînages ,
    Le résultat obtenu est trié par ordre croissant.
 
 *@retourner: la tete du chainage obtenu par la fusion.
 *@param: les tetes de deux chainages à fusionner.
 *@PRE: les deux chainage doit etre terminés par nullptr,
    et doit etre triés par ordre croissant.
 *@POST:
*/
p_data fusion(p_data prem, p_data sec) { 

    p_data restDeChain=sec; // une variable pour sauvegarder la rest du chainage
    p_data tmpDeprem = prem; // l'element courant de premier chainage
    p_data tmpDeSec = sec; // l'element courant de deuxieme chainage
   
    
    while (restDeChain != nullptr ) { 
            
        bool ok = true; // pour arreter la deuxieme boucle
        tmpDeprem = prem;
        tmpDeSec = restDeChain;

       while (tmpDeprem != nullptr && ok ) { 

            if (((tmpDeprem->suiv)==nullptr))  { // ajouter a la fin du chainage

                tmpDeprem->suiv = tmpDeSec; 
                restDeChain = tmpDeSec->suiv;
                tmpDeSec->suiv = nullptr;
                ok = false; 

              // ajouter au milieu du chainage  
            } else if ((tmpDeSec->valeur >= tmpDeprem->valeur) && ((tmpDeSec->valeur <= (tmpDeprem->suiv)->valeur))){ 

                restDeChain = tmpDeSec->suiv;
                tmpDeSec->suiv = tmpDeprem->suiv;
                tmpDeprem->suiv = tmpDeSec;
                ok = false; 

                // ajouter au debut
            } else if ((tmpDeSec->valeur <= tmpDeprem->valeur)) { 

               restDeChain = tmpDeSec->suiv;
                tmpDeSec->suiv = tmpDeprem;
                prem = tmpDeSec;
                ok = false;   
                
            } else { 
                
                tmpDeprem = tmpDeprem->suiv;

            }
            
        }
 
    }         
     
    return prem; 

}

p_data fusionRec(p_data prem, p_data sec, p_data tmpPrem) { 
 
  if (sec==nullptr) { 

   return prem; 

  } else if (prem == nullptr){ 
    return sec;

  }else{

    if (((tmpPrem->suiv)==nullptr)) {

      tmpPrem->suiv = sec; 
      p_data restChain = sec->suiv;
      sec->suiv = nullptr;

      return fusionRec(prem,restChain,tmpPrem); 

    } else if ((sec->valeur >= tmpPrem->valeur) && ((sec->valeur <= (tmpPrem->suiv)->valeur))) {

      p_data restChain = sec->suiv;
      sec->suiv = tmpPrem->suiv;
      tmpPrem->suiv = sec;

      fusionRec(prem,restChain,tmpPrem);

    } else if ((sec->valeur <= prem->valeur)) { 

      p_data restChain = sec->suiv;
      sec->suiv = tmpPrem;
      prem = sec;

      fusionRec(prem,restChain,tmpPrem);

    }  else { 

      fusionRec(prem,sec,tmpPrem->suiv); 

    }     


  }
   
}


/**
  *@Role:une fonction qui compte le nombre de 
    monotonies croissantes dans un chaînage.
  *@retourner: le nombre de monotonies croissantes.
  *@param: la tete de chainage.
  *@PRE:le chainage ne doit etre vide et il doit terminer par nullptr 

*/
int nbCroissances(p_data chain){
  // creer une pointeur de type p_data
  p_data maillonAComp = chain;

  //nbMonotonies est initialisé par 1 pour le cas ou il y a
  // une seule monotonies
  int nbMonotonies = 1;

  //parcourir le chainage
  while(maillonAComp->suiv != nullptr){
    
    // si la prochain maillon est plus petit que le maillon courant donc
    // il y a une nouvelle monotonies
    if(maillonAComp->valeur >= (maillonAComp->suiv)->valeur){
      nbMonotonies++;
    }

    maillonAComp = maillonAComp->suiv;
     
  }
  
  return nbMonotonies;

}



/**
 *@Role: une procédure qui place dans le chaînage mono la première 
   monotonie croissante de chain et l’en retire.
 *@param:les tetes de deux chainage mono pour placer la monotonie et 
   chain pour extraire la monotonie.
 *@PRE: chain and mono ne doit pas etres vides

**/
void extraireCroissance(p_data & chain, p_data & mono){
  p_data queueDeSeg; // creer une pointeur vers la queue de la monotonies 
  p_data teteDeSeg; // creer une pointeur vers la tete de la monotonies
  queueDeSeg = chain; 
  teteDeSeg = chain;

  //boucle pour chercher la queue de la monotonies
  while(((queueDeSeg->suiv) != nullptr) && ((queueDeSeg->valeur) < ((queueDeSeg->suiv)->valeur)) ){
    queueDeSeg = (queueDeSeg->suiv);
  }

  // retirer la monotonies de la chainage (chain)
  chain = (queueDeSeg->suiv);

  // ajouter la monotonies à la fin de la chainage (mono)
  (queueDeSeg->suiv) = nullptr;
  addChain(teteDeSeg , mono);
}


/***fin des fonctions et procédures de chainage***/
//-------------------------------------------------------------------------


//----------------Monotonie---------------------------------------

/**
 *@Role:une fonction qui crée et renvoie une structure (de type datalistes) 
   initialisée avec un tableau de nb chaînages (non valués).
 *@param: le nombre de chainage dans le tableau.
 *@retourner: un tableau (de type datalistes) 
 *@PRE: nb doit être supérieur à 0.
**/
datalistes initT(int nb){
  // creer un nouveau tableau 
  datalistes newTab;
  newTab.capa = nb;
  newTab.nbmono = 0;

  //allocation du tableau
  newTab.monotonies = (p_data*)malloc(nb*sizeof(p_data));


  //parcourir le tableau pour rendre chaque pointeur egals à nullptr
  for(int i =0 ; i < newTab.capa ; i++){
    newTab.monotonies[i] = nullptr;
  }
  return newTab;
}

/**
 *@Role:une procédure qui ajoute dans le tableau mono le 
   chaînage chain (dans la prochaine case non utilisée).
 *@param: la tete de chainage chain et le tableau
 *@PRE: mono doit etre déjà alloué  

**/
void ajouterFin(p_data chain , datalistes & mono){

  // verifier que il y a une place pour la nouvelle chainage
  if(mono.nbmono + 1 <= mono.capa){

   mono.monotonies[mono.nbmono] = chain; // ajouter la nouvelle chainage 
   mono.nbmono++;

  }else{
    // afficher une message en cas il n'y a pas une place vide
    cout << "il n'y a pas une place vide dans le tableau" << endl;

  }
 
}

/**
  *@Role:une procédure qui affiche (une ligne par case) les valeurs 
    stockées dans le tableau mono.
  *@param: le tableau à afficher
  *@PRE
  *@POST

**/
void affT(datalistes mono){

  for(int i =0 ; i < mono.nbmono ; i++){
    
    aff(mono.monotonies[i]);
    cout << " " <<endl;
  }

}
/**
 *@Role:une fonction qui supprime la dernier élément de le tableau mono
 *@param: le tableau (mono)
 *@retourner: la nouvelle dernier élément apres la suppression
 *@PRE: la nombre des éléments doit etre supérieur ou egal a 2
**/
p_data suppressionFin(datalistes & mono){
  mono.monotonies[mono.nbmono-1] = NULL; // supprimer la dernier élément

  mono.nbmono = (mono.nbmono -1); 

  return mono.monotonies[mono.nbmono-1]; // retourner la dernier élément

}

/**
  *@Role:une fonction qui renvoie un chaînage formé en mettant bout à bout (dans l’ordre) 
     tous les chaînages stockés dans le tableau mono, en les y enlevant.
  *@param: le tableau 
  *@retourner: la tete de chainage formé par la fonction.
  @PRE: the list mono must have at least one element

**/
p_data suppressionTotale(datalistes & mono){
  p_data teteDeCahin;
  p_data queueDeChain;

  //ajouter la première élément du tableau
  teteDeCahin = mono.monotonies[0];

  //supprimer la première élément du tableau
  mono.monotonies[0] = NULL;

  queueDeChain = teteDeCahin;

  // ajouter la rest des éléments
  for(int i= 1; i < mono.nbmono ; i++){
    while((queueDeChain->suiv) != nullptr){
      queueDeChain = (queueDeChain->suiv);
    }
    (queueDeChain->suiv) = mono.monotonies[i];

    mono.monotonies[i] = NULL;

  }

  mono.nbmono = 0;
  free(mono.monotonies); // desalloue le tableau

  return teteDeCahin;

}


//----------------------------fusion multiple----------------------------

/**
 *@Role:une fonction retournant un tableau dont les cases contiennent (dans l’ordre) 
   les monotonies croissantes du chaînage contenu dans chain.
 *@param: la tete du chainage (chain)
 *@retourner: le tableau
 *@PRE: chain ne doit pas etre vide
 *@POST: chain doit contenir le pointeur null.

**/
datalistes separation(p_data & chain){
  int nbElem = nbCroissances(chain);

  // creer le tableau
  datalistes tab = initT(nbElem);


  // ajouter les monotonies croissantes du chaînage à le tableau
  for(int i = 0 ; i < nbElem ; i++){

    extraireCroissance(chain, tab.monotonies[i]);
    tab.nbmono++;
  }
  return tab;
}

/**
 *@Role:une procédure qui effectue une fusion multiple des 
   monotonies stockées dans le tableau avec la première monotonies
 *@param: le tableau à trier
 *@PRE: tabmono ne doit pas etre vide

**/
void trier(datalistes & tabmono){

  // parcourir chaque monotonies du tableau
  // et la ajouter dans la première monotonie
  for(int i = 1 ; i < (tabmono.nbmono) ; i++){

    // fusioner la monotonie courant monotonie avec la première monotonie
    tabmono.monotonies[0] = fusion(tabmono.monotonies[0],tabmono.monotonies[i]);

    //supprimer la monotonie courant
    tabmono.monotonies[i] = nullptr; 

  }
  tabmono.nbmono = 1;


}


/**
 * @Role:une procédure qui trie un chaînage en utilisant une fusion multiple.
 * @PRE:
 * @POST:
 * @param: la tete du chainage

* */ 

void trierChain(p_data & chain){
  // Utiliser la fonction separation pour creer une table 

  datalistes list = separation(chain);

  //trier la table en utilisant la fonction trier 

  trier(list);

  // Utiliser la fonction suppressionTotale qui retourner une chainage 
  // de tous les éléments de la table (list)

  chain = suppressionTotale(list);

}



















int main(){

  //---------------test Chainage ------------------//
  
  /*************test ajouteDevant et aff --marche bien avec char , string , long-- **************/
  /*
  p_data ptrdata = new data;
  (*ptrdata).valeur =125;
  (*ptrdata).suiv = nullptr;

  cout << "test ajouteDevant et aff" <<endl;

  cout <<"afficher le chainage avant utiliser ajoutDevant"<<endl;
  aff(ptrdata);

  cout <<"afficher le chainage apres utiliser ajoutDevant"<<endl;
  ptrdata = ajoutDevant(15,ptrdata);
  aff(ptrdata);
  */

  /*******test saisieBorne --marche bien avec string, char , long  ***********/
  /*
  cout << "test saisieBorne" <<endl;
  p_data ptrdata;
  ptrdata = saisieBorne(5);
  aff(ptrdata);
  */

  /***********test saisieNombre   --marche bien avec string, char , long ************/
  /*
  p_data ptrdata;
  cout << "test saisieNombre" <<endl;
  ptrdata = saisieNombre(3);
  aff(ptrdata);
  */

  /***************test fusion -- marche bien avec string, char , long*****************/
  /*
  p_data ptrdata;
  p_data ptrdata2;
  p_data ptrdata3;

  // ajouter des maillons a ptrdata et ptrdata2
  cout << "test fusion" <<endl;

  cout << "ajouter des maillons a ptrdata" <<endl;
  ptrdata = saisieNombre(3);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);
  cout << "ajouter des maillons a ptrdata2" <<endl;
  ptrdata2 = saisieNombre(4);
  cout << "afficher  ptrdata2" <<endl;
  aff(ptrdata2);

  cout << "affichage de la fusion de deux chainage ptrdata et ptrdata2" <<endl;
  ptrdata3 = fusion(ptrdata, ptrdata2);
  aff(ptrdata3);

  */

  /***************test fusionRec -- marche bien avec string, char , long*****************/
  /*
  p_data ptrdata;
  p_data ptrdata2;
  p_data ptrdata3;

  // ajouter des maillons a ptrdata et ptrdata2
  cout << "test fusionRec" <<endl;

  cout << "ajouter des maillons a ptrdata" <<endl;
  ptrdata = saisieNombre(3);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);
  cout << "ajouter des maillons a ptrdata2" <<endl;
  ptrdata2 = saisieNombre(2);
  cout << "afficher  ptrdata2" <<endl;
  aff(ptrdata2);

  cout << "affichage de la fusion de deux chainage ptrdata et ptrdata2" <<endl;
  ptrdata3 = fusionRec(ptrdata, ptrdata2,ptrdata);
  aff(ptrdata3);
  */
  



  /*************test nbCroissance -- marche bien avec string, char , long************/
  /*
  p_data ptrdata;
  cout << "ajouter des maillons a ptrdata" << endl;
  ptrdata = saisieNombre(3);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);

  cout << "test nbCroissance de ptrdata" << endl;
  cout << nbCroissances(ptrdata) << endl;
  */


  /***** test addChain (fonction supplémentaire) -- marche bien avec string, char , long ******/
  /*
  p_data ptrdata = nullptr;
  p_data ptrdata2;

  cout << "test addChain" << endl;

  cout << "ajouter des maillons a ptrdata2" <<endl;
  ptrdata2 = saisieNombre(2);
  cout << "afficher  ptrdata2" <<endl;
  aff(ptrdata2);
  
  cout << "ajoute ptrdata2 a la fin de ptrdate" << endl;
  addChain(ptrdata2 ,ptrdata);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);
  */

  /*******test extraireCroissance -marche bien avec string, char , long-**********/
  /*
  p_data ptrdata;
  p_data ptrdata2 = nullptr;

  cout << "ajouter des maillons a ptrdata" <<endl;
  ptrdata = saisieNombre(3);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);

  
  cout << "test extraireCroissance" <<endl;
 
  extraireCroissance(ptrdata,ptrdata2);
  aff(ptrdata2);
  */
 

 //--------------test Monotonies----------------------

 /*****************test initT - marche bien*****************/
 /*
 datalistes tab1;
 cout << "test initT" <<endl;
 tab1 = initT(15);

 cout << "Ecrire tab1.capa " <<endl;
 cout << tab1.capa << endl;

 cout << "Ecrire tab1.nbmono " <<endl;
 cout << tab1.nbmono << endl;
 */

 
 /**********ajouterFin et affT -marche bien avec string, char , long- *******/
 /*
 p_data ptrdata;
 p_data ptrdata2;

 datalistes tab1;
 tab1 = initT(15);


 cout << "ajouter des maillons a ptrdata" <<endl;
 ptrdata = saisieNombre(3);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);
  cout << "ajouter des maillons a ptrdata2" <<endl;
  ptrdata2 = saisieNombre(2);
  cout << "afficher  ptrdata2" <<endl;
  aff(ptrdata2);
 
 //testing ajouterFin --works fine--
 cout << "test ajouterFin" <<endl;

 cout << "ajouter ptrdata a la fin du tableau " <<endl;
 ajouterFin(ptrdata , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 cout << "ajouter ptrdata a la fin du tableau " <<endl;
 ajouterFin(ptrdata2 , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 
 cout << "afficher le tableau" <<endl;
 affT(tab1);

 */

 
 /************ test suppressionFin  -- marche bien avec string, char , long********/
 /*
 cout << "test suppressionFin" <<endl;


 p_data ptrdata;
 p_data ptrdata2;

 datalistes tab1;

 tab1 = initT(15);


 cout << "ajouter des maillons a ptrdata" <<endl;
 ptrdata = saisieNombre(3);
 cout << "afficher  ptrdata" <<endl;
 aff(ptrdata);

 cout << "ajouter des maillons a ptrdata2" <<endl;
 ptrdata2 = saisieNombre(2);
 cout << "afficher  ptrdata2" <<endl;
 aff(ptrdata2);


 cout << "ajouter ptrdata a la fin du tableau " <<endl;
 ajouterFin(ptrdata , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 cout << "ajouter ptrdata2 a la fin du tableau " <<endl;
 ajouterFin(ptrdata2 , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 cout << "afficher le tableau avant supprimer le dernier élément " <<endl;
 affT(tab1);

 suppressionFin(tab1);

 cout << "afficher le tableau apres supprimer le dernier élément " <<endl;
 affT(tab1);
 */

 /**********testing suppressionTotale  - marche bien avec string, char , long*****/
 /*
 cout << "testing suppressionTotale" << endl;

 p_data ptrdata;
 p_data ptrdata2;
 p_data ptrdata3;

 datalistes tab1;

 tab1 = initT(15);


 cout << "ajouter des maillons a ptrdata" <<endl;
 ptrdata = saisieNombre(3);
 cout << "afficher  ptrdata" <<endl;
 aff(ptrdata);

 cout << "ajouter des maillons a ptrdata2" <<endl;
 ptrdata2 = saisieNombre(2);
 cout << "afficher  ptrdata2" <<endl;
 aff(ptrdata2);


 cout << "ajouter ptrdata a la fin du tableau " <<endl;
 ajouterFin(ptrdata , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 cout << "ajouter ptrdata a la fin du tableau " <<endl;
 ajouterFin(ptrdata2 , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 
 cout << "afficher le tableau avant supprimer tous les elements " <<endl;
 affT(tab1);


 ptrdata3 = suppressionTotale(tab1);

 cout << "afficher le tableau apres supprimer tous les elements " <<endl;
 affT(tab1);

 cout << "afficher le chainage de tous les elements supprime" << endl;
 aff(ptrdata3);
 */
 


 //------------------------fusion multiple ---------------------


 /**************test separation - marche bien avec string, char , long************/
 /*
 p_data ptrdata;
 
 cout << "ajouter des maillons a ptrdata" <<endl;
 ptrdata = saisieNombre(5);
 cout << "afficher  ptrdata" <<endl;
 aff(ptrdata);

 datalistes tab1;

 tab1 = separation(ptrdata);

 cout << "afficher le tableau tab1" << endl;
 affT(tab1);
 cout << "Ecrire tab1.capa " << tab1.capa << endl;
 cout << "Ecrire tab1.nbmono " << tab1.nbmono << endl;
 cout << "afficher le chainage" << endl;
 aff(ptrdata);
 */
 
 /**************test trier - marche bien avec string, char , long*********/
 /*

 cout << "test trier" <<endl;

 datalistes tab1;
 tab1 = initT(15);

 p_data ptrdata;
 p_data ptrdata2;


 
 cout << "ajouter des maillons a ptrdata" <<endl;
 ptrdata = saisieNombre(3);
 cout << "afficher  ptrdata" <<endl;
 aff(ptrdata);

 cout << "ajouter des maillons a ptrdata2" <<endl;
 ptrdata2 = saisieNombre(5);
 cout << "afficher  ptrdata2" <<endl;
 aff(ptrdata2);


 cout << "ajouter ptrdata a la fin du tableau " <<endl;
 ajouterFin(ptrdata , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;

 cout << "ajouter ptrdata2 a la fin du tableau " <<endl;
 ajouterFin(ptrdata2 , tab1);
 cout << "Ecrire la nombre des element du tableau" <<endl;
 cout << tab1.nbmono << endl;
 
 cout << "afficher le tableau avant trier " <<endl;
 affT(tab1);
 
 cout << "afficher le tableau apres trier  " <<endl;

 trier(tab1);

 affT(tab1);
 */
 
 /*****test trierChain(p_data & chain) - marche bien avec string, char , long**********/
 /*
  cout << "test trierChain" <<endl;
  
  p_data ptrdata ;


  cout << "ajouter des maillons a ptrdata" <<endl;
  ptrdata = saisieNombre(5);
  cout << "afficher  ptrdata" <<endl;
  aff(ptrdata);

  cout << "afficher le chainage Avant le trier" << endl;
  aff(ptrdata);
  trierChain(ptrdata);
  cout << "afficher le chainage apres le trier" << endl;
  aff(ptrdata);
 */

}