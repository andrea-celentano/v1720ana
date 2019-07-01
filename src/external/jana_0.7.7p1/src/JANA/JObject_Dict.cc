// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIjana_0dO7dO7p1dIsrcdIJANAdIJObject_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "src/external/jana_0.7.7p1/src/JANA/JObject.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_janacLcLJObject(void *p = 0);
   static void *newArray_janacLcLJObject(Long_t size, void *p);
   static void delete_janacLcLJObject(void *p);
   static void deleteArray_janacLcLJObject(void *p);
   static void destruct_janacLcLJObject(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jana::JObject*)
   {
      ::jana::JObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jana::JObject >(0);
      static ::ROOT::TGenericClassInfo 
         instance("jana::JObject", ::jana::JObject::Class_Version(), "JObject.h", 58,
                  typeid(::jana::JObject), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jana::JObject::Dictionary, isa_proxy, 4,
                  sizeof(::jana::JObject) );
      instance.SetNew(&new_janacLcLJObject);
      instance.SetNewArray(&newArray_janacLcLJObject);
      instance.SetDelete(&delete_janacLcLJObject);
      instance.SetDeleteArray(&deleteArray_janacLcLJObject);
      instance.SetDestructor(&destruct_janacLcLJObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jana::JObject*)
   {
      return GenerateInitInstanceLocal((::jana::JObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jana::JObject*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace jana {
//______________________________________________________________________________
atomic_TClass_ptr JObject::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *JObject::Class_Name()
{
   return "jana::JObject";
}

//______________________________________________________________________________
const char *JObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jana::JObject*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int JObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jana::JObject*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *JObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jana::JObject*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *JObject::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jana::JObject*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace jana
namespace jana {
//______________________________________________________________________________
void JObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class jana::JObject.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jana::JObject::Class(),this);
   } else {
      R__b.WriteClassBuffer(jana::JObject::Class(),this);
   }
}

} // namespace jana
namespace ROOT {
   // Wrappers around operator new
   static void *new_janacLcLJObject(void *p) {
      return  p ? new(p) ::jana::JObject : new ::jana::JObject;
   }
   static void *newArray_janacLcLJObject(Long_t nElements, void *p) {
      return p ? new(p) ::jana::JObject[nElements] : new ::jana::JObject[nElements];
   }
   // Wrapper around operator delete
   static void delete_janacLcLJObject(void *p) {
      delete ((::jana::JObject*)p);
   }
   static void deleteArray_janacLcLJObject(void *p) {
      delete [] ((::jana::JObject*)p);
   }
   static void destruct_janacLcLJObject(void *p) {
      typedef ::jana::JObject current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::jana::JObject

namespace ROOT {
   static TClass *vectorlEjanacLcLJObjectmUgR_Dictionary();
   static void vectorlEjanacLcLJObjectmUgR_TClassManip(TClass*);
   static void *new_vectorlEjanacLcLJObjectmUgR(void *p = 0);
   static void *newArray_vectorlEjanacLcLJObjectmUgR(Long_t size, void *p);
   static void delete_vectorlEjanacLcLJObjectmUgR(void *p);
   static void deleteArray_vectorlEjanacLcLJObjectmUgR(void *p);
   static void destruct_vectorlEjanacLcLJObjectmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<jana::JObject*>*)
   {
      vector<jana::JObject*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<jana::JObject*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<jana::JObject*>", -2, "vector", 464,
                  typeid(vector<jana::JObject*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEjanacLcLJObjectmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<jana::JObject*>) );
      instance.SetNew(&new_vectorlEjanacLcLJObjectmUgR);
      instance.SetNewArray(&newArray_vectorlEjanacLcLJObjectmUgR);
      instance.SetDelete(&delete_vectorlEjanacLcLJObjectmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEjanacLcLJObjectmUgR);
      instance.SetDestructor(&destruct_vectorlEjanacLcLJObjectmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<jana::JObject*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<jana::JObject*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEjanacLcLJObjectmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<jana::JObject*>*)0x0)->GetClass();
      vectorlEjanacLcLJObjectmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEjanacLcLJObjectmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEjanacLcLJObjectmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<jana::JObject*> : new vector<jana::JObject*>;
   }
   static void *newArray_vectorlEjanacLcLJObjectmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<jana::JObject*>[nElements] : new vector<jana::JObject*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEjanacLcLJObjectmUgR(void *p) {
      delete ((vector<jana::JObject*>*)p);
   }
   static void deleteArray_vectorlEjanacLcLJObjectmUgR(void *p) {
      delete [] ((vector<jana::JObject*>*)p);
   }
   static void destruct_vectorlEjanacLcLJObjectmUgR(void *p) {
      typedef vector<jana::JObject*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<jana::JObject*>

namespace {
  void TriggerDictionaryInitialization_JObject_Dict_Impl() {
    static const char* headers[] = {
"src/external/jana_0.7.7p1/src/JANA/JObject.h",
0
    };
    static const char* includePaths[] = {
"/work/jlab_software/2.0/Darwin_macosx10.14-x86_64-clang10.0.1/xercesc/3.1.3/include",
"/work/jlab_software/2.0/Darwin_macosx10.14-x86_64-clang10.0.1/ccdb/ccdb-1.06.00/include",
"/work/v1720ana/src/external",
"/work/v1720ana/src/libraries",
"/work/v1720ana/src/plugins",
"/work/v1720ana",
"/work/v1720ana/src/external/jana_0.7.7p1/src",
"/work/v1720ana/src/external/jana_0.7.7p1/src/JANA",
"/work/v1720ana/src/external/jana_0.7.7p1/src/plugins",
"/work/jlab_software/2.0/Darwin_macosx10.14-x86_64-clang10.0.0/root/6.12.06/include",
"/work/v1720ana/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "JObject_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace jana{class __attribute__((annotate("$clingAutoload$src/external/jana_0.7.7p1/src/JANA/JObject.h")))  JObject;}
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$iosfwd")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "JObject_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/jana_0.7.7p1/src/JANA/JObject.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"jana::JObject", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("JObject_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_JObject_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_JObject_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_JObject_Dict() {
  TriggerDictionaryInitialization_JObject_Dict_Impl();
}
