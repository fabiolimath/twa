#!/usr/bin/awk -f

BEGIN{
      range=162;
      
      Db = 0;
      Dc = 0;
      T  = 0;
      F  = 0;
   }

   {ln++;}     

   {Db += $1;} 
   {Dc += $2;} 
   {T  += $3;} 
   {F  += $4;} 

ln==range{
      Db = Db/range;
      Dc = Dc/range;
      T  = T/range;
      F  = F/range;
      
      print Db, Dc, T, F;
      
      Db = 0;
      Dc = 0;
      T  = 0;
      F  = 0;
      ln = 0;
   }