#include <stdbool.h>
#include <assert.h>
#include<stdio.h>
#include "zbior_ary.h"

int main() {
 /* // A = {2, 7, 12}
  zbior_ary A = ciag_arytmetyczny(2, 5, 12);
  assert(moc(A) == 3);
  assert(ary(A) == 1);
  // B = {4, 9, 14, 19}
  zbior_ary B = ciag_arytmetyczny(4, 5, 19);
  // C = {1}
  zbior_ary C = singleton(1);
  // D = {1, 4, 9, 14, 19}
  zbior_ary D = suma(B, C);
  // E = {1, 2, 4, 7, 9, 12, 14, 19}
  zbior_ary E = suma(D, A);
  assert(moc(E) == 8);
  // F = {14}
  zbior_ary F = singleton(14);
  // G = {1, 2, 4, 7, 9, 12, 19}
  zbior_ary G = roznica(E, F);
  assert(ary(G) == 4);
  assert(nalezy(G, 4));
  assert(!nalezy(G, 5));
  // H = {4, 9, 19};
  zbior_ary H = iloczyn(G, B);
  assert(moc(H) == 3);
  assert(ary(H) == 2);
  // I = {}
  zbior_ary I = iloczyn(H, A);
  assert(moc(I) == 0);
  printf("siu"); */
  zbior_ary A = ciag_arytmetyczny(2, 5, 17);
  A = suma(A, ciag_arytmetyczny(27, 5, 32));
  A = suma(A, ciag_arytmetyczny(29, 5, 39));
  A = suma(A, singleton(54));
  A = suma(A, singleton(18));
  A = suma(A, singleton(24));
  A = suma(A, singleton(14));
  A = suma(A, ciag_arytmetyczny(3, 5, 8));
  zbior_ary B = singleton(4);
  B = suma(B, singleton(37));
  B = suma(B, singleton(22));
  B = suma(B, singleton(12));
  B = suma(B, singleton(32));
  B = suma(B, singleton(2));
  B = suma(B, ciag_arytmetyczny(3, 5, 13));
  B = suma(B, ciag_arytmetyczny(14, 5, 24));
  B = suma(B, ciag_arytmetyczny(39, 5, 44));
  B = suma(B, ciag_arytmetyczny(54, 5, 59));
  Wyczytaj(A);
  Wyczytaj(B);
  Wyczytaj(suma(A,B));
  Wyczytaj(roznica(A,B));
  Wyczytaj(iloczyn(A,B));
  printf("%d   %d    %d", moc(suma(A,B)), moc(roznica(A,B)), moc(iloczyn(A, B)));
  printf("\n %d    %d    %d", ary(suma(A,B)), ary(roznica(A,B)), ary(iloczyn(A, B)));
  return 0;
}
