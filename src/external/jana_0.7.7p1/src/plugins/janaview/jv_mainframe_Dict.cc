// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIjana_0dO7dO7p1dIsrcdIpluginsdIjanaviewdIjv_mainframe_Dict

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
#include "src/external/jana_0.7.7p1/src/plugins/janaview/jv_mainframe.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_jv_mainframe(void *p);
   static void deleteArray_jv_mainframe(void *p);
   static void destruct_jv_mainframe(void *p);
   static void streamer_jv_mainframe(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jv_mainframe*)
   {
      ::jv_mainframe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jv_mainframe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("jv_mainframe", ::jv_mainframe::Class_Version(), "plugins/janaview/jv_mainframe.h", 65,
                  typeid(::jv_mainframe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jv_mainframe::Dictionary, isa_proxy, 16,
                  sizeof(::jv_mainframe) );
      instance.SetDelete(&delete_jv_mainframe);
      instance.SetDeleteArray(&deleteArray_jv_mainframe);
      instance.SetDestructor(&destruct_jv_mainframe);
      instance.SetStreamerFunc(&streamer_jv_mainframe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jv_mainframe*)
   {
      return GenerateInitInstanceLocal((::jv_mainframe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jv_mainframe*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr jv_mainframe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *jv_mainframe::Class_Name()
{
   return "jv_mainframe";
}

//______________________________________________________________________________
const char *jv_mainframe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jv_mainframe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int jv_mainframe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jv_mainframe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jv_mainframe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jv_mainframe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jv_mainframe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jv_mainframe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void jv_mainframe::Streamer(TBuffer &R__b)
{
   // Stream an object of class jv_mainframe.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b >> lSource;
      R__b >> lRun;
      R__b >> lEvent;
      R__b >> lObjectType;
      R__b >> lObjectValue;
      R__b >> lbObjectTypes;
      R__b >> lbObjects;
      R__b >> lbAssociatedObjects;
      R__b >> lbAssociatedToObjects;
      R__b >> lbObjectValues;
      R__b >> fTab;
      R__b >> fCanvas;
      R__b >> canvas;
      {
         vector<string> &R__stl =  objtypes;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      {
         vector<void*> &R__stl =  vobjs;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(void *));
         if (R__tcl1==0) {
            Error("vobjs streamer","Missing the TClass object for void *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            void* R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      R__b >> timer;
      R__b >> sleep_time;
      R__b >> delayed_object_type_id;
      R__b.CheckByteCount(R__s, R__c, jv_mainframe::IsA());
   } else {
      R__c = R__b.WriteVersion(jv_mainframe::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b << lSource;
      R__b << lRun;
      R__b << lEvent;
      R__b << lObjectType;
      R__b << lObjectValue;
      R__b << lbObjectTypes;
      R__b << lbObjects;
      R__b << lbAssociatedObjects;
      R__b << lbAssociatedToObjects;
      R__b << lbObjectValues;
      R__b << fTab;
      R__b << fCanvas;
      R__b << canvas;
      {
         vector<string> &R__stl =  objtypes;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      {
         vector<void*> &R__stl =  vobjs;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(void *));
         if (R__tcl1==0) {
            Error("vobjs streamer","Missing the TClass object for void *!");
            return;
         }
            vector<void*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((void*)&(*R__k),R__tcl1);
            }
         }
      }
      R__b << timer;
      R__b << sleep_time;
      R__b << delayed_object_type_id;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_jv_mainframe(void *p) {
      delete ((::jv_mainframe*)p);
   }
   static void deleteArray_jv_mainframe(void *p) {
      delete [] ((::jv_mainframe*)p);
   }
   static void destruct_jv_mainframe(void *p) {
      typedef ::jv_mainframe current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_jv_mainframe(TBuffer &buf, void *obj) {
      ((::jv_mainframe*)obj)->::jv_mainframe::Streamer(buf);
   }
} // end of namespace ROOT for class ::jv_mainframe

namespace ROOT {
   static TClass *vectorlEvoidmUgR_Dictionary();
   static void vectorlEvoidmUgR_TClassManip(TClass*);
   static void *new_vectorlEvoidmUgR(void *p = 0);
   static void *newArray_vectorlEvoidmUgR(Long_t size, void *p);
   static void delete_vectorlEvoidmUgR(void *p);
   static void deleteArray_vectorlEvoidmUgR(void *p);
   static void destruct_vectorlEvoidmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<void*>*)
   {
      vector<void*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<void*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<void*>", -2, "vector", 464,
                  typeid(vector<void*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvoidmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<void*>) );
      instance.SetNew(&new_vectorlEvoidmUgR);
      instance.SetNewArray(&newArray_vectorlEvoidmUgR);
      instance.SetDelete(&delete_vectorlEvoidmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvoidmUgR);
      instance.SetDestructor(&destruct_vectorlEvoidmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<void*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<void*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvoidmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<void*>*)0x0)->GetClass();
      vectorlEvoidmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvoidmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvoidmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<void*> : new vector<void*>;
   }
   static void *newArray_vectorlEvoidmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<void*>[nElements] : new vector<void*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvoidmUgR(void *p) {
      delete ((vector<void*>*)p);
   }
   static void deleteArray_vectorlEvoidmUgR(void *p) {
      delete [] ((vector<void*>*)p);
   }
   static void destruct_vectorlEvoidmUgR(void *p) {
      typedef vector<void*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<void*>

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 464,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace {
  void TriggerDictionaryInitialization_jv_mainframe_Dict_Impl() {
    static const char* headers[] = {
"src/external/jana_0.7.7p1/src/plugins/janaview/jv_mainframe.h",
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
#line 1 "jv_mainframe_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/jana_0.7.7p1/src/plugins/janaview/jv_mainframe.h")))  jv_mainframe;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "jv_mainframe_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/jana_0.7.7p1/src/plugins/janaview/jv_mainframe.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"jv_mainframe", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("jv_mainframe_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_jv_mainframe_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_jv_mainframe_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_jv_mainframe_Dict() {
  TriggerDictionaryInitialization_jv_mainframe_Dict_Impl();
}
