// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIlibrariesdIsystemdIv1720Object_Dict

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
#include "src/libraries/system/v1720Object.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_v1720Object(void *p = 0);
   static void *newArray_v1720Object(Long_t size, void *p);
   static void delete_v1720Object(void *p);
   static void deleteArray_v1720Object(void *p);
   static void destruct_v1720Object(void *p);
   static void streamer_v1720Object(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::v1720Object*)
   {
      ::v1720Object *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::v1720Object >(0);
      static ::ROOT::TGenericClassInfo 
         instance("v1720Object", ::v1720Object::Class_Version(), "system/v1720Object.h", 21,
                  typeid(::v1720Object), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::v1720Object::Dictionary, isa_proxy, 16,
                  sizeof(::v1720Object) );
      instance.SetNew(&new_v1720Object);
      instance.SetNewArray(&newArray_v1720Object);
      instance.SetDelete(&delete_v1720Object);
      instance.SetDeleteArray(&deleteArray_v1720Object);
      instance.SetDestructor(&destruct_v1720Object);
      instance.SetStreamerFunc(&streamer_v1720Object);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::v1720Object*)
   {
      return GenerateInitInstanceLocal((::v1720Object*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::v1720Object*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr v1720Object::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *v1720Object::Class_Name()
{
   return "v1720Object";
}

//______________________________________________________________________________
const char *v1720Object::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::v1720Object*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int v1720Object::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::v1720Object*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *v1720Object::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::v1720Object*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *v1720Object::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::v1720Object*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void v1720Object::Streamer(TBuffer &R__b)
{
   // Stream an object of class v1720Object.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      //This works around a msvc bug and should be harmless on other platforms
      typedef jana::JObject baseClass0;
      baseClass0::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, v1720Object::IsA());
   } else {
      R__c = R__b.WriteVersion(v1720Object::IsA(), kTRUE);
      //This works around a msvc bug and should be harmless on other platforms
      typedef jana::JObject baseClass0;
      baseClass0::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_v1720Object(void *p) {
      return  p ? new(p) ::v1720Object : new ::v1720Object;
   }
   static void *newArray_v1720Object(Long_t nElements, void *p) {
      return p ? new(p) ::v1720Object[nElements] : new ::v1720Object[nElements];
   }
   // Wrapper around operator delete
   static void delete_v1720Object(void *p) {
      delete ((::v1720Object*)p);
   }
   static void deleteArray_v1720Object(void *p) {
      delete [] ((::v1720Object*)p);
   }
   static void destruct_v1720Object(void *p) {
      typedef ::v1720Object current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_v1720Object(TBuffer &buf, void *obj) {
      ((::v1720Object*)obj)->::v1720Object::Streamer(buf);
   }
} // end of namespace ROOT for class ::v1720Object

namespace {
  void TriggerDictionaryInitialization_v1720Object_Dict_Impl() {
    static const char* headers[] = {
"src/libraries/system/v1720Object.h",
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
"/work/jlab_software/2.0/Darwin_macosx10.14-x86_64-clang10.0.0/root/6.12.06/include",
"/work/v1720ana/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "v1720Object_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/libraries/system/v1720Object.h")))  v1720Object;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "v1720Object_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/libraries/system/v1720Object.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"v1720Object", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("v1720Object_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_v1720Object_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_v1720Object_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_v1720Object_Dict() {
  TriggerDictionaryInitialization_v1720Object_Dict_Impl();
}
