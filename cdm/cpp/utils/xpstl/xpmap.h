/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#ifndef __XPMAP_H__
#define __XPMAP_H__

#include "xparray.h"

template <class KEY, class TYPE>
class CXpMap
{
  protected:

  struct SNode
  {
    SNode(const KEY& Key, const TYPE& Value) : m_Key(Key), m_Value(Value) {}
    virtual ~SNode() {}

    KEY                 m_Key;
    TYPE                m_Value;
  };

  typedef CXpArray<SNode*> CPtrArray;

  CPtrArray             m_SortedArray;
  public:

  CXpMap(const int nGrowBy = 10);
  CXpMap(const CXpMap& Map);
  virtual ~CXpMap();

  INT_PTR Insert(const KEY& Key, const TYPE& Value);

  void Remove(const KEY& Key);
  void RemoveAll();

  inline INT_PTR GetCount() const;

  inline bool HasKey(const KEY& Key) const;
  inline INT_PTR FindKey(const KEY& Key) const;
  inline bool FindValue(const KEY& Key, TYPE& Value) const;

  inline const KEY& GetKey(const INT_PTR nIndex) const;
  inline KEY& GetKey(const INT_PTR nIndex);

  inline const TYPE& GetValue(const INT_PTR nIndex) const;
  inline TYPE& GetValue(const INT_PTR nIndex);

  inline void GetPair(const INT_PTR nIndex, KEY& Key, TYPE& Value) const  ;

  inline CXpMap Union(const CXpMap& Right) const;
  inline CXpMap Intersection(const CXpMap& Right) const;
  inline CXpMap Difference(const CXpMap& Right) const;

  inline const TYPE& operator[](const INT_PTR nIndex) const;
  inline TYPE& operator[](const INT_PTR nIndex);
  
  HRESULT Copy(const CXpMap& Map);

  bool operator==(const CXpMap& Map) const;
  CXpMap& operator=(const CXpMap& Map);

  protected:
  bool BinarySearch(const KEY& Key, INT_PTR& nIndex) const;
};

#include "xpmap.inl"

#endif //__XPMAP_H__
