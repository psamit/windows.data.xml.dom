// Copyright (c) The NodeRT Contributors
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
// IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
//
// See the Apache Version 2.0 License for specific language governing permissions
// and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Data { namespace Xml { namespace Dom { 
  v8::Local<v8::Value> WrapDtdEntity(::Windows::Data::Xml::Dom::DtdEntity^ wintRtInstance);
  ::Windows::Data::Xml::Dom::DtdEntity^ UnwrapDtdEntity(Local<Value> value);
  
  v8::Local<v8::Value> WrapDtdNotation(::Windows::Data::Xml::Dom::DtdNotation^ wintRtInstance);
  ::Windows::Data::Xml::Dom::DtdNotation^ UnwrapDtdNotation(Local<Value> value);
  
  v8::Local<v8::Value> WrapIXmlCharacterData(::Windows::Data::Xml::Dom::IXmlCharacterData^ wintRtInstance);
  ::Windows::Data::Xml::Dom::IXmlCharacterData^ UnwrapIXmlCharacterData(Local<Value> value);
  
  v8::Local<v8::Value> WrapIXmlNode(::Windows::Data::Xml::Dom::IXmlNode^ wintRtInstance);
  ::Windows::Data::Xml::Dom::IXmlNode^ UnwrapIXmlNode(Local<Value> value);
  
  v8::Local<v8::Value> WrapIXmlNodeSelector(::Windows::Data::Xml::Dom::IXmlNodeSelector^ wintRtInstance);
  ::Windows::Data::Xml::Dom::IXmlNodeSelector^ UnwrapIXmlNodeSelector(Local<Value> value);
  
  v8::Local<v8::Value> WrapIXmlNodeSerializer(::Windows::Data::Xml::Dom::IXmlNodeSerializer^ wintRtInstance);
  ::Windows::Data::Xml::Dom::IXmlNodeSerializer^ UnwrapIXmlNodeSerializer(Local<Value> value);
  
  v8::Local<v8::Value> WrapIXmlText(::Windows::Data::Xml::Dom::IXmlText^ wintRtInstance);
  ::Windows::Data::Xml::Dom::IXmlText^ UnwrapIXmlText(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlAttribute(::Windows::Data::Xml::Dom::XmlAttribute^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlAttribute^ UnwrapXmlAttribute(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlCDataSection(::Windows::Data::Xml::Dom::XmlCDataSection^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlCDataSection^ UnwrapXmlCDataSection(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlComment(::Windows::Data::Xml::Dom::XmlComment^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlComment^ UnwrapXmlComment(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlDocument(::Windows::Data::Xml::Dom::XmlDocument^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlDocument^ UnwrapXmlDocument(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlDocumentFragment(::Windows::Data::Xml::Dom::XmlDocumentFragment^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlDocumentFragment^ UnwrapXmlDocumentFragment(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlDocumentType(::Windows::Data::Xml::Dom::XmlDocumentType^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlDocumentType^ UnwrapXmlDocumentType(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlDomImplementation(::Windows::Data::Xml::Dom::XmlDomImplementation^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlDomImplementation^ UnwrapXmlDomImplementation(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlElement(::Windows::Data::Xml::Dom::XmlElement^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlElement^ UnwrapXmlElement(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlEntityReference(::Windows::Data::Xml::Dom::XmlEntityReference^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlEntityReference^ UnwrapXmlEntityReference(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlLoadSettings(::Windows::Data::Xml::Dom::XmlLoadSettings^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlLoadSettings^ UnwrapXmlLoadSettings(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlNamedNodeMap(::Windows::Data::Xml::Dom::XmlNamedNodeMap^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ UnwrapXmlNamedNodeMap(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlNodeList(::Windows::Data::Xml::Dom::XmlNodeList^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlNodeList^ UnwrapXmlNodeList(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlProcessingInstruction(::Windows::Data::Xml::Dom::XmlProcessingInstruction^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ UnwrapXmlProcessingInstruction(Local<Value> value);
  
  v8::Local<v8::Value> WrapXmlText(::Windows::Data::Xml::Dom::XmlText^ wintRtInstance);
  ::Windows::Data::Xml::Dom::XmlText^ UnwrapXmlText(Local<Value> value);
  



  static void InitNodeTypeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("NodeType").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("invalid").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::Invalid)));
    Nan::Set(enumObject, Nan::New<String>("elementNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::ElementNode)));
    Nan::Set(enumObject, Nan::New<String>("attributeNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::AttributeNode)));
    Nan::Set(enumObject, Nan::New<String>("textNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::TextNode)));
    Nan::Set(enumObject, Nan::New<String>("dataSectionNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::DataSectionNode)));
    Nan::Set(enumObject, Nan::New<String>("entityReferenceNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::EntityReferenceNode)));
    Nan::Set(enumObject, Nan::New<String>("entityNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::EntityNode)));
    Nan::Set(enumObject, Nan::New<String>("processingInstructionNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::ProcessingInstructionNode)));
    Nan::Set(enumObject, Nan::New<String>("commentNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::CommentNode)));
    Nan::Set(enumObject, Nan::New<String>("documentNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::DocumentNode)));
    Nan::Set(enumObject, Nan::New<String>("documentTypeNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::DocumentTypeNode)));
    Nan::Set(enumObject, Nan::New<String>("documentFragmentNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::DocumentFragmentNode)));
    Nan::Set(enumObject, Nan::New<String>("notationNode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Data::Xml::Dom::NodeType::NotationNode)));
  }



  class DtdEntity : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("DtdEntity").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("notationName").ToLocalChecked(), NotationNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicId").ToLocalChecked(), PublicIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemId").ToLocalChecked(), SystemIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("DtdEntity").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      DtdEntity(::Windows::Data::Xml::Dom::DtdEntity^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::DtdEntity^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::DtdEntity^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DtdEntity *wrapperInstance = new DtdEntity(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::DtdEntity^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::DtdEntity^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapDtdEntity(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void NotationNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NotationName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->PublicId;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->SystemId;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdEntity^>(info.This())) {
        return;
      }

      DtdEntity *wrapper = DtdEntity::Unwrap<DtdEntity>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::DtdEntity^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapDtdEntity(::Windows::Data::Xml::Dom::DtdEntity^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::DtdEntity^ UnwrapDtdEntity(Local<Value> value);
  };

  Persistent<FunctionTemplate> DtdEntity::s_constructorTemplate;

  v8::Local<v8::Value> WrapDtdEntity(::Windows::Data::Xml::Dom::DtdEntity^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DtdEntity::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::DtdEntity^ UnwrapDtdEntity(Local<Value> value) {
     return DtdEntity::Unwrap<DtdEntity>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDtdEntity(Local<Object> exports) {
    DtdEntity::Init(exports);
  }

  class DtdNotation : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("DtdNotation").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicId").ToLocalChecked(), PublicIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemId").ToLocalChecked(), SystemIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("DtdNotation").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      DtdNotation(::Windows::Data::Xml::Dom::DtdNotation^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::DtdNotation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::DtdNotation^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DtdNotation *wrapperInstance = new DtdNotation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::DtdNotation^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::DtdNotation^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapDtdNotation(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PublicIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->PublicId;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->SystemId;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::DtdNotation^>(info.This())) {
        return;
      }

      DtdNotation *wrapper = DtdNotation::Unwrap<DtdNotation>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::DtdNotation^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapDtdNotation(::Windows::Data::Xml::Dom::DtdNotation^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::DtdNotation^ UnwrapDtdNotation(Local<Value> value);
  };

  Persistent<FunctionTemplate> DtdNotation::s_constructorTemplate;

  v8::Local<v8::Value> WrapDtdNotation(::Windows::Data::Xml::Dom::DtdNotation^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DtdNotation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::DtdNotation^ UnwrapDtdNotation(Local<Value> value) {
     return DtdNotation::Unwrap<DtdNotation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDtdNotation(Local<Object> exports) {
    DtdNotation::Init(exports);
  }

  class IXmlCharacterData : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IXmlCharacterData").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "substringData", SubstringData);
            Nan::SetPrototypeMethod(localRef, "appendData", AppendData);
            Nan::SetPrototypeMethod(localRef, "insertData", InsertData);
            Nan::SetPrototypeMethod(localRef, "deleteData", DeleteData);
            Nan::SetPrototypeMethod(localRef, "replaceData", ReplaceData);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IXmlCharacterData").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IXmlCharacterData(::Windows::Data::Xml::Dom::IXmlCharacterData^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::IXmlCharacterData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::IXmlCharacterData^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IXmlCharacterData *wrapperInstance = new IXmlCharacterData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::IXmlCharacterData^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::IXmlCharacterData^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIXmlCharacterData(winRtInstance));
    }


    static void SubstringData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->SubstringData(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->AppendData(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->InsertData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DeleteData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->DeleteData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      if (info.Length() == 3
        && info[0]->IsUint32()
        && info[1]->IsUint32()
        && info[2]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          wrapper->_instance->ReplaceData(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Data = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlCharacterData^>(info.This())) {
        return;
      }

      IXmlCharacterData *wrapper = IXmlCharacterData::Unwrap<IXmlCharacterData>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::IXmlCharacterData^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIXmlCharacterData(::Windows::Data::Xml::Dom::IXmlCharacterData^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::IXmlCharacterData^ UnwrapIXmlCharacterData(Local<Value> value);
  };

  Persistent<FunctionTemplate> IXmlCharacterData::s_constructorTemplate;

  v8::Local<v8::Value> WrapIXmlCharacterData(::Windows::Data::Xml::Dom::IXmlCharacterData^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IXmlCharacterData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::IXmlCharacterData^ UnwrapIXmlCharacterData(Local<Value> value) {
     return IXmlCharacterData::Unwrap<IXmlCharacterData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIXmlCharacterData(Local<Object> exports) {
    IXmlCharacterData::Init(exports);
  }

  class IXmlNode : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IXmlNode").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IXmlNode").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IXmlNode(::Windows::Data::Xml::Dom::IXmlNode^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::IXmlNode^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::IXmlNode^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IXmlNode *wrapperInstance = new IXmlNode(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::IXmlNode^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::IXmlNode^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIXmlNode(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info.This())) {
        return;
      }

      IXmlNode *wrapper = IXmlNode::Unwrap<IXmlNode>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::IXmlNode^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIXmlNode(::Windows::Data::Xml::Dom::IXmlNode^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::IXmlNode^ UnwrapIXmlNode(Local<Value> value);
  };

  Persistent<FunctionTemplate> IXmlNode::s_constructorTemplate;

  v8::Local<v8::Value> WrapIXmlNode(::Windows::Data::Xml::Dom::IXmlNode^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IXmlNode::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::IXmlNode^ UnwrapIXmlNode(Local<Value> value) {
     return IXmlNode::Unwrap<IXmlNode>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIXmlNode(Local<Object> exports) {
    IXmlNode::Init(exports);
  }

  class IXmlNodeSelector : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IXmlNodeSelector").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IXmlNodeSelector").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IXmlNodeSelector(::Windows::Data::Xml::Dom::IXmlNodeSelector^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::IXmlNodeSelector^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSelector^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::IXmlNodeSelector^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IXmlNodeSelector *wrapperInstance = new IXmlNodeSelector(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSelector^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::IXmlNodeSelector^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::IXmlNodeSelector^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIXmlNodeSelector(winRtInstance));
    }


    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSelector^>(info.This())) {
        return;
      }

      IXmlNodeSelector *wrapper = IXmlNodeSelector::Unwrap<IXmlNodeSelector>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSelector^>(info.This())) {
        return;
      }

      IXmlNodeSelector *wrapper = IXmlNodeSelector::Unwrap<IXmlNodeSelector>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSelector^>(info.This())) {
        return;
      }

      IXmlNodeSelector *wrapper = IXmlNodeSelector::Unwrap<IXmlNodeSelector>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSelector^>(info.This())) {
        return;
      }

      IXmlNodeSelector *wrapper = IXmlNodeSelector::Unwrap<IXmlNodeSelector>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Data::Xml::Dom::IXmlNodeSelector^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIXmlNodeSelector(::Windows::Data::Xml::Dom::IXmlNodeSelector^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::IXmlNodeSelector^ UnwrapIXmlNodeSelector(Local<Value> value);
  };

  Persistent<FunctionTemplate> IXmlNodeSelector::s_constructorTemplate;

  v8::Local<v8::Value> WrapIXmlNodeSelector(::Windows::Data::Xml::Dom::IXmlNodeSelector^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IXmlNodeSelector::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::IXmlNodeSelector^ UnwrapIXmlNodeSelector(Local<Value> value) {
     return IXmlNodeSelector::Unwrap<IXmlNodeSelector>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIXmlNodeSelector(Local<Object> exports) {
    IXmlNodeSelector::Init(exports);
  }

  class IXmlNodeSerializer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IXmlNodeSerializer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IXmlNodeSerializer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IXmlNodeSerializer(::Windows::Data::Xml::Dom::IXmlNodeSerializer^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::IXmlNodeSerializer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSerializer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::IXmlNodeSerializer^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IXmlNodeSerializer *wrapperInstance = new IXmlNodeSerializer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSerializer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::IXmlNodeSerializer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::IXmlNodeSerializer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIXmlNodeSerializer(winRtInstance));
    }


    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSerializer^>(info.This())) {
        return;
      }

      IXmlNodeSerializer *wrapper = IXmlNodeSerializer::Unwrap<IXmlNodeSerializer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSerializer^>(info.This())) {
        return;
      }

      IXmlNodeSerializer *wrapper = IXmlNodeSerializer::Unwrap<IXmlNodeSerializer>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNodeSerializer^>(info.This())) {
        return;
      }

      IXmlNodeSerializer *wrapper = IXmlNodeSerializer::Unwrap<IXmlNodeSerializer>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::IXmlNodeSerializer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIXmlNodeSerializer(::Windows::Data::Xml::Dom::IXmlNodeSerializer^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::IXmlNodeSerializer^ UnwrapIXmlNodeSerializer(Local<Value> value);
  };

  Persistent<FunctionTemplate> IXmlNodeSerializer::s_constructorTemplate;

  v8::Local<v8::Value> WrapIXmlNodeSerializer(::Windows::Data::Xml::Dom::IXmlNodeSerializer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IXmlNodeSerializer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::IXmlNodeSerializer^ UnwrapIXmlNodeSerializer(Local<Value> value) {
     return IXmlNodeSerializer::Unwrap<IXmlNodeSerializer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIXmlNodeSerializer(Local<Object> exports) {
    IXmlNodeSerializer::Init(exports);
  }

  class IXmlText : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IXmlText").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "splitText", SplitText);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IXmlText").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IXmlText(::Windows::Data::Xml::Dom::IXmlText^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::IXmlText^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlText^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::IXmlText^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IXmlText *wrapperInstance = new IXmlText(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlText^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::IXmlText^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::IXmlText^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIXmlText(winRtInstance));
    }


    static void SplitText(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlText^>(info.This())) {
        return;
      }

      IXmlText *wrapper = IXmlText::Unwrap<IXmlText>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlText^ result;
          result = wrapper->_instance->SplitText(arg0);
          info.GetReturnValue().Set(WrapIXmlText(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Data::Xml::Dom::IXmlText^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIXmlText(::Windows::Data::Xml::Dom::IXmlText^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::IXmlText^ UnwrapIXmlText(Local<Value> value);
  };

  Persistent<FunctionTemplate> IXmlText::s_constructorTemplate;

  v8::Local<v8::Value> WrapIXmlText(::Windows::Data::Xml::Dom::IXmlText^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IXmlText::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::IXmlText^ UnwrapIXmlText(Local<Value> value) {
     return IXmlText::Unwrap<IXmlText>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIXmlText(Local<Object> exports) {
    IXmlText::Init(exports);
  }

  class XmlAttribute : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlAttribute").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter, ValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("specified").ToLocalChecked(), SpecifiedGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlAttribute").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlAttribute(::Windows::Data::Xml::Dom::XmlAttribute^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlAttribute^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlAttribute^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlAttribute *wrapperInstance = new XmlAttribute(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlAttribute^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlAttribute^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlAttribute(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Value;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Value = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SpecifiedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        bool result = wrapper->_instance->Specified;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info.This())) {
        return;
      }

      XmlAttribute *wrapper = XmlAttribute::Unwrap<XmlAttribute>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlAttribute^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlAttribute(::Windows::Data::Xml::Dom::XmlAttribute^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlAttribute^ UnwrapXmlAttribute(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlAttribute::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlAttribute(::Windows::Data::Xml::Dom::XmlAttribute^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlAttribute::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlAttribute^ UnwrapXmlAttribute(Local<Value> value) {
     return XmlAttribute::Unwrap<XmlAttribute>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlAttribute(Local<Object> exports) {
    XmlAttribute::Init(exports);
  }

  class XmlCDataSection : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlCDataSection").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "splitText", SplitText);
            Nan::SetPrototypeMethod(localRef, "substringData", SubstringData);
            Nan::SetPrototypeMethod(localRef, "appendData", AppendData);
            Nan::SetPrototypeMethod(localRef, "insertData", InsertData);
            Nan::SetPrototypeMethod(localRef, "deleteData", DeleteData);
            Nan::SetPrototypeMethod(localRef, "replaceData", ReplaceData);
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlCDataSection").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlCDataSection(::Windows::Data::Xml::Dom::XmlCDataSection^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlCDataSection^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlCDataSection^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlCDataSection *wrapperInstance = new XmlCDataSection(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlCDataSection^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlCDataSection^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlCDataSection(winRtInstance));
    }


    static void SplitText(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlText^ result;
          result = wrapper->_instance->SplitText(arg0);
          info.GetReturnValue().Set(WrapIXmlText(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SubstringData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->SubstringData(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->AppendData(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->InsertData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DeleteData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->DeleteData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 3
        && info[0]->IsUint32()
        && info[1]->IsUint32()
        && info[2]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          wrapper->_instance->ReplaceData(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Data = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlCDataSection^>(info.This())) {
        return;
      }

      XmlCDataSection *wrapper = XmlCDataSection::Unwrap<XmlCDataSection>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlCDataSection^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlCDataSection(::Windows::Data::Xml::Dom::XmlCDataSection^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlCDataSection^ UnwrapXmlCDataSection(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlCDataSection::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlCDataSection(::Windows::Data::Xml::Dom::XmlCDataSection^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlCDataSection::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlCDataSection^ UnwrapXmlCDataSection(Local<Value> value) {
     return XmlCDataSection::Unwrap<XmlCDataSection>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlCDataSection(Local<Object> exports) {
    XmlCDataSection::Init(exports);
  }

  class XmlComment : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlComment").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "substringData", SubstringData);
            Nan::SetPrototypeMethod(localRef, "appendData", AppendData);
            Nan::SetPrototypeMethod(localRef, "insertData", InsertData);
            Nan::SetPrototypeMethod(localRef, "deleteData", DeleteData);
            Nan::SetPrototypeMethod(localRef, "replaceData", ReplaceData);
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlComment").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlComment(::Windows::Data::Xml::Dom::XmlComment^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlComment^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlComment^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlComment *wrapperInstance = new XmlComment(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlComment^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlComment^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlComment(winRtInstance));
    }


    static void SubstringData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->SubstringData(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->AppendData(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->InsertData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DeleteData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->DeleteData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 3
        && info[0]->IsUint32()
        && info[1]->IsUint32()
        && info[2]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          wrapper->_instance->ReplaceData(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Data = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlComment^>(info.This())) {
        return;
      }

      XmlComment *wrapper = XmlComment::Unwrap<XmlComment>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlComment^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlComment(::Windows::Data::Xml::Dom::XmlComment^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlComment^ UnwrapXmlComment(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlComment::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlComment(::Windows::Data::Xml::Dom::XmlComment^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlComment::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlComment^ UnwrapXmlComment(Local<Value> value) {
     return XmlComment::Unwrap<XmlComment>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlComment(Local<Object> exports) {
    XmlComment::Init(exports);
  }

  class XmlDocument : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlDocument").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "loadXmlFromBuffer", LoadXmlFromBuffer);
            Nan::SetPrototypeMethod(localRef, "createElement", CreateElement);
            Nan::SetPrototypeMethod(localRef, "createDocumentFragment", CreateDocumentFragment);
            Nan::SetPrototypeMethod(localRef, "createTextNode", CreateTextNode);
            Nan::SetPrototypeMethod(localRef, "createComment", CreateComment);
            Nan::SetPrototypeMethod(localRef, "createProcessingInstruction", CreateProcessingInstruction);
            Nan::SetPrototypeMethod(localRef, "createAttribute", CreateAttribute);
            Nan::SetPrototypeMethod(localRef, "createEntityReference", CreateEntityReference);
            Nan::SetPrototypeMethod(localRef, "getElementsByTagName", GetElementsByTagName);
            Nan::SetPrototypeMethod(localRef, "createCDataSection", CreateCDataSection);
            Nan::SetPrototypeMethod(localRef, "createAttributeNS", CreateAttributeNS);
            Nan::SetPrototypeMethod(localRef, "createElementNS", CreateElementNS);
            Nan::SetPrototypeMethod(localRef, "getElementById", GetElementById);
            Nan::SetPrototypeMethod(localRef, "importNode", ImportNode);
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
            Nan::SetPrototypeMethod(localRef, "loadXml", LoadXml);
          

          
            Nan::SetPrototypeMethod(localRef, "saveToFileAsync", SaveToFileAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("doctype").ToLocalChecked(), DoctypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("documentElement").ToLocalChecked(), DocumentElementGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("documentUri").ToLocalChecked(), DocumentUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("implementation").ToLocalChecked(), ImplementationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(LoadFromUriAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("loadFromUriAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(LoadFromFileAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("loadFromFileAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("XmlDocument").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlDocument(::Windows::Data::Xml::Dom::XmlDocument^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlDocument^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlDocument^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Data::Xml::Dom::XmlDocument();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlDocument *wrapperInstance = new XmlDocument(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlDocument^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlDocument^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlDocument(winRtInstance));
    }

    static void SaveToFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = dynamic_cast<::Windows::Storage::IStorageFile^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->SaveToFileAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void LoadXmlFromBuffer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->LoadXmlFromBuffer(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info[1]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Data::Xml::Dom::XmlLoadSettings^ arg1 = UnwrapXmlLoadSettings(info[1]);
          
          wrapper->_instance->LoadXmlFromBuffer(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateElement(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlElement^ result;
          result = wrapper->_instance->CreateElement(arg0);
          info.GetReturnValue().Set(WrapXmlElement(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateDocumentFragment(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocumentFragment^ result;
          result = wrapper->_instance->CreateDocumentFragment();
          info.GetReturnValue().Set(WrapXmlDocumentFragment(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateTextNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlText^ result;
          result = wrapper->_instance->CreateTextNode(arg0);
          info.GetReturnValue().Set(WrapXmlText(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateComment(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlComment^ result;
          result = wrapper->_instance->CreateComment(arg0);
          info.GetReturnValue().Set(WrapXmlComment(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateProcessingInstruction(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ result;
          result = wrapper->_instance->CreateProcessingInstruction(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlProcessingInstruction(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateAttribute(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->CreateAttribute(arg0);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateEntityReference(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlEntityReference^ result;
          result = wrapper->_instance->CreateEntityReference(arg0);
          info.GetReturnValue().Set(WrapXmlEntityReference(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetElementsByTagName(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->GetElementsByTagName(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateCDataSection(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlCDataSection^ result;
          result = wrapper->_instance->CreateCDataSection(arg0);
          info.GetReturnValue().Set(WrapXmlCDataSection(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateAttributeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->CreateAttributeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateElementNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          ::Windows::Data::Xml::Dom::XmlElement^ result;
          result = wrapper->_instance->CreateElementNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlElement(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetElementById(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlElement^ result;
          result = wrapper->_instance->GetElementById(arg0);
          info.GetReturnValue().Set(WrapXmlElement(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ImportNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && info[1]->IsBoolean())
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          bool arg1 = Nan::To<bool>(info[1]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ImportNode(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void LoadXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->LoadXml(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Data::Xml::Dom::XmlLoadSettings^ arg1 = UnwrapXmlLoadSettings(info[1]);
          
          wrapper->_instance->LoadXml(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void LoadFromUriAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Data::Xml::Dom::XmlDocument^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
            
          op = ::Windows::Data::Xml::Dom::XmlDocument::LoadFromUriAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info[1]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Data::Xml::Dom::XmlLoadSettings^ arg1 = UnwrapXmlLoadSettings(info[1]);
            
          op = ::Windows::Data::Xml::Dom::XmlDocument::LoadFromUriAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Data::Xml::Dom::XmlDocument^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapXmlDocument(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void LoadFromFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Data::Xml::Dom::XmlDocument^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = dynamic_cast<::Windows::Storage::IStorageFile^>(NodeRT::Utils::GetObjectInstance(info[0]));
            
          op = ::Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info[1]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = dynamic_cast<::Windows::Storage::IStorageFile^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Data::Xml::Dom::XmlLoadSettings^ arg1 = UnwrapXmlLoadSettings(info[1]);
            
          op = ::Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Data::Xml::Dom::XmlDocument^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapXmlDocument(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void DoctypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocumentType^ result = wrapper->_instance->Doctype;
        info.GetReturnValue().Set(WrapXmlDocumentType(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DocumentElementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlElement^ result = wrapper->_instance->DocumentElement;
        info.GetReturnValue().Set(WrapXmlElement(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DocumentUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DocumentUri;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ImplementationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDomImplementation^ result = wrapper->_instance->Implementation;
        info.GetReturnValue().Set(WrapXmlDomImplementation(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info.This())) {
        return;
      }

      XmlDocument *wrapper = XmlDocument::Unwrap<XmlDocument>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlDocument^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlDocument(::Windows::Data::Xml::Dom::XmlDocument^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlDocument^ UnwrapXmlDocument(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlDocument::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlDocument(::Windows::Data::Xml::Dom::XmlDocument^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlDocument::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlDocument^ UnwrapXmlDocument(Local<Value> value) {
     return XmlDocument::Unwrap<XmlDocument>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlDocument(Local<Object> exports) {
    XmlDocument::Init(exports);
  }

  class XmlDocumentFragment : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlDocumentFragment").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlDocumentFragment").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlDocumentFragment(::Windows::Data::Xml::Dom::XmlDocumentFragment^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlDocumentFragment^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlDocumentFragment^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlDocumentFragment *wrapperInstance = new XmlDocumentFragment(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlDocumentFragment^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlDocumentFragment^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlDocumentFragment(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentFragment^>(info.This())) {
        return;
      }

      XmlDocumentFragment *wrapper = XmlDocumentFragment::Unwrap<XmlDocumentFragment>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlDocumentFragment^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlDocumentFragment(::Windows::Data::Xml::Dom::XmlDocumentFragment^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlDocumentFragment^ UnwrapXmlDocumentFragment(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlDocumentFragment::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlDocumentFragment(::Windows::Data::Xml::Dom::XmlDocumentFragment^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlDocumentFragment::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlDocumentFragment^ UnwrapXmlDocumentFragment(Local<Value> value) {
     return XmlDocumentFragment::Unwrap<XmlDocumentFragment>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlDocumentFragment(Local<Object> exports) {
    XmlDocumentFragment::Init(exports);
  }

  class XmlDocumentType : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlDocumentType").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("entities").ToLocalChecked(), EntitiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("notations").ToLocalChecked(), NotationsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlDocumentType").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlDocumentType(::Windows::Data::Xml::Dom::XmlDocumentType^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlDocumentType^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlDocumentType^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlDocumentType *wrapperInstance = new XmlDocumentType(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlDocumentType^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlDocumentType^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlDocumentType(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void EntitiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Entities;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NotationsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Notations;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocumentType^>(info.This())) {
        return;
      }

      XmlDocumentType *wrapper = XmlDocumentType::Unwrap<XmlDocumentType>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlDocumentType^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlDocumentType(::Windows::Data::Xml::Dom::XmlDocumentType^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlDocumentType^ UnwrapXmlDocumentType(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlDocumentType::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlDocumentType(::Windows::Data::Xml::Dom::XmlDocumentType^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlDocumentType::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlDocumentType^ UnwrapXmlDocumentType(Local<Value> value) {
     return XmlDocumentType::Unwrap<XmlDocumentType>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlDocumentType(Local<Object> exports) {
    XmlDocumentType::Init(exports);
  }

  class XmlDomImplementation : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlDomImplementation").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasFeature", HasFeature);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlDomImplementation").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlDomImplementation(::Windows::Data::Xml::Dom::XmlDomImplementation^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlDomImplementation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDomImplementation^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlDomImplementation^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlDomImplementation *wrapperInstance = new XmlDomImplementation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDomImplementation^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlDomImplementation^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlDomImplementation^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlDomImplementation(winRtInstance));
    }


    static void HasFeature(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDomImplementation^>(info.This())) {
        return;
      }

      XmlDomImplementation *wrapper = XmlDomImplementation::Unwrap<XmlDomImplementation>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          bool result;
          result = wrapper->_instance->HasFeature(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Data::Xml::Dom::XmlDomImplementation^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlDomImplementation(::Windows::Data::Xml::Dom::XmlDomImplementation^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlDomImplementation^ UnwrapXmlDomImplementation(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlDomImplementation::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlDomImplementation(::Windows::Data::Xml::Dom::XmlDomImplementation^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlDomImplementation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlDomImplementation^ UnwrapXmlDomImplementation(Local<Value> value) {
     return XmlDomImplementation::Unwrap<XmlDomImplementation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlDomImplementation(Local<Object> exports) {
    XmlDomImplementation::Init(exports);
  }

  class XmlElement : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlElement").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getAttribute", GetAttribute);
            Nan::SetPrototypeMethod(localRef, "setAttribute", SetAttribute);
            Nan::SetPrototypeMethod(localRef, "removeAttribute", RemoveAttribute);
            Nan::SetPrototypeMethod(localRef, "getAttributeNode", GetAttributeNode);
            Nan::SetPrototypeMethod(localRef, "setAttributeNode", SetAttributeNode);
            Nan::SetPrototypeMethod(localRef, "removeAttributeNode", RemoveAttributeNode);
            Nan::SetPrototypeMethod(localRef, "getElementsByTagName", GetElementsByTagName);
            Nan::SetPrototypeMethod(localRef, "setAttributeNS", SetAttributeNS);
            Nan::SetPrototypeMethod(localRef, "getAttributeNS", GetAttributeNS);
            Nan::SetPrototypeMethod(localRef, "removeAttributeNS", RemoveAttributeNS);
            Nan::SetPrototypeMethod(localRef, "setAttributeNodeNS", SetAttributeNodeNS);
            Nan::SetPrototypeMethod(localRef, "getAttributeNodeNS", GetAttributeNodeNS);
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tagName").ToLocalChecked(), TagNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlElement").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlElement(::Windows::Data::Xml::Dom::XmlElement^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlElement^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlElement^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlElement *wrapperInstance = new XmlElement(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlElement^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlElement^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlElement(winRtInstance));
    }


    static void GetAttribute(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          Platform::String^ result;
          result = wrapper->_instance->GetAttribute(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetAttribute(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->SetAttribute(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveAttribute(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->RemoveAttribute(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetAttributeNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->GetAttributeNode(arg0);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetAttributeNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlAttribute^ arg0 = UnwrapXmlAttribute(info[0]);
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->SetAttributeNode(arg0);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveAttributeNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlAttribute^ arg0 = UnwrapXmlAttribute(info[0]);
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->RemoveAttributeNode(arg0);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetElementsByTagName(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->GetElementsByTagName(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetAttributeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString()
        && info[2]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          wrapper->_instance->SetAttributeNS(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetAttributeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          Platform::String^ result;
          result = wrapper->_instance->GetAttributeNS(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveAttributeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->RemoveAttributeNS(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetAttributeNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlAttribute^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlAttribute^ arg0 = UnwrapXmlAttribute(info[0]);
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->SetAttributeNodeNS(arg0);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetAttributeNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          ::Windows::Data::Xml::Dom::XmlAttribute^ result;
          result = wrapper->_instance->GetAttributeNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlAttribute(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void TagNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->TagName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlElement^>(info.This())) {
        return;
      }

      XmlElement *wrapper = XmlElement::Unwrap<XmlElement>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlElement^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlElement(::Windows::Data::Xml::Dom::XmlElement^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlElement^ UnwrapXmlElement(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlElement::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlElement(::Windows::Data::Xml::Dom::XmlElement^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlElement::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlElement^ UnwrapXmlElement(Local<Value> value) {
     return XmlElement::Unwrap<XmlElement>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlElement(Local<Object> exports) {
    XmlElement::Init(exports);
  }

  class XmlEntityReference : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlEntityReference").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlEntityReference").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlEntityReference(::Windows::Data::Xml::Dom::XmlEntityReference^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlEntityReference^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlEntityReference^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlEntityReference *wrapperInstance = new XmlEntityReference(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlEntityReference^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlEntityReference^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlEntityReference(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlEntityReference^>(info.This())) {
        return;
      }

      XmlEntityReference *wrapper = XmlEntityReference::Unwrap<XmlEntityReference>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlEntityReference^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlEntityReference(::Windows::Data::Xml::Dom::XmlEntityReference^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlEntityReference^ UnwrapXmlEntityReference(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlEntityReference::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlEntityReference(::Windows::Data::Xml::Dom::XmlEntityReference^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlEntityReference::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlEntityReference^ UnwrapXmlEntityReference(Local<Value> value) {
     return XmlEntityReference::Unwrap<XmlEntityReference>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlEntityReference(Local<Object> exports) {
    XmlEntityReference::Init(exports);
  }

  class XmlLoadSettings : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlLoadSettings").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("validateOnParse").ToLocalChecked(), ValidateOnParseGetter, ValidateOnParseSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("resolveExternals").ToLocalChecked(), ResolveExternalsGetter, ResolveExternalsSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prohibitDtd").ToLocalChecked(), ProhibitDtdGetter, ProhibitDtdSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxElementDepth").ToLocalChecked(), MaxElementDepthGetter, MaxElementDepthSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("elementContentWhiteSpace").ToLocalChecked(), ElementContentWhiteSpaceGetter, ElementContentWhiteSpaceSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlLoadSettings").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlLoadSettings(::Windows::Data::Xml::Dom::XmlLoadSettings^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlLoadSettings^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlLoadSettings^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Data::Xml::Dom::XmlLoadSettings();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlLoadSettings *wrapperInstance = new XmlLoadSettings(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlLoadSettings^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlLoadSettings^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlLoadSettings(winRtInstance));
    }





    static void ValidateOnParseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try  {
        bool result = wrapper->_instance->ValidateOnParse;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ValidateOnParseSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ValidateOnParse = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ResolveExternalsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try  {
        bool result = wrapper->_instance->ResolveExternals;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ResolveExternalsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ResolveExternals = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ProhibitDtdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try  {
        bool result = wrapper->_instance->ProhibitDtd;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProhibitDtdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ProhibitDtd = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MaxElementDepthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try  {
        unsigned int result = wrapper->_instance->MaxElementDepth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MaxElementDepthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->MaxElementDepth = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ElementContentWhiteSpaceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try  {
        bool result = wrapper->_instance->ElementContentWhiteSpace;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ElementContentWhiteSpaceSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlLoadSettings^>(info.This())) {
        return;
      }

      XmlLoadSettings *wrapper = XmlLoadSettings::Unwrap<XmlLoadSettings>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ElementContentWhiteSpace = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlLoadSettings^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlLoadSettings(::Windows::Data::Xml::Dom::XmlLoadSettings^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlLoadSettings^ UnwrapXmlLoadSettings(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlLoadSettings::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlLoadSettings(::Windows::Data::Xml::Dom::XmlLoadSettings^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlLoadSettings::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlLoadSettings^ UnwrapXmlLoadSettings(Local<Value> value) {
     return XmlLoadSettings::Unwrap<XmlLoadSettings>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlLoadSettings(Local<Object> exports) {
    XmlLoadSettings::Init(exports);
  }

  class XmlNamedNodeMap : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlNamedNodeMap").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "item", Item);
            Nan::SetPrototypeMethod(localRef, "getNamedItem", GetNamedItem);
            Nan::SetPrototypeMethod(localRef, "setNamedItem", SetNamedItem);
            Nan::SetPrototypeMethod(localRef, "removeNamedItem", RemoveNamedItem);
            Nan::SetPrototypeMethod(localRef, "getNamedItemNS", GetNamedItemNS);
            Nan::SetPrototypeMethod(localRef, "removeNamedItemNS", RemoveNamedItemNS);
            Nan::SetPrototypeMethod(localRef, "setNamedItemNS", SetNamedItemNS);
            Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
            Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
            Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
            Nan::SetPrototypeMethod(localRef, "first", First);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlNamedNodeMap").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlNamedNodeMap(::Windows::Data::Xml::Dom::XmlNamedNodeMap^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlNamedNodeMap^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlNamedNodeMap *wrapperInstance = new XmlNamedNodeMap(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlNamedNodeMap^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlNamedNodeMap(winRtInstance));
    }


    static void Item(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->Item(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetNamedItem(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->GetNamedItem(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetNamedItem(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SetNamedItem(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveNamedItem(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveNamedItem(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetNamedItemNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->GetNamedItemNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveNamedItemNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveNamedItemNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetNamedItemNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SetNamedItemNS(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IndexOf(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          unsigned int arg1;
          
          bool result;
          result = wrapper->_instance->IndexOf(arg0, &arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Boolean>(result));
          Nan::Set(resObj, Nan::New<String>("index").ToLocalChecked(), Nan::New<Integer>(arg1));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetMany(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          ::Platform::Array<::Windows::Data::Xml::Dom::IXmlNode^>^ arg1 = ref new ::Platform::Array<::Windows::Data::Xml::Dom::IXmlNode^>(wrapper->_instance->Length - arg0);
          
          unsigned int result;
          result = wrapper->_instance->GetMany(arg0, arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("number").ToLocalChecked(), Nan::New<Integer>(result));
          Nan::Set(resObj, Nan::New<String>("items").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Data::Xml::Dom::IXmlNode^>::CreateArrayWrapper(arg1, 
            [](::Windows::Data::Xml::Dom::IXmlNode^ val) -> Local<Value> {
              return WrapIXmlNode(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(value);
            },
            [](Local<Value> value) -> ::Windows::Data::Xml::Dom::IXmlNode^ {
              return UnwrapIXmlNode(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Data::Xml::Dom::IXmlNode^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Data::Xml::Dom::IXmlNode^>::CreateIteratorWrapper(result, 
            [](::Windows::Data::Xml::Dom::IXmlNode^ val) -> Local<Value> {
              return WrapIXmlNode(val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNamedNodeMap^>(info.This())) {
        return;
      }

      XmlNamedNodeMap *wrapper = XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlNamedNodeMap(::Windows::Data::Xml::Dom::XmlNamedNodeMap^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ UnwrapXmlNamedNodeMap(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlNamedNodeMap::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlNamedNodeMap(::Windows::Data::Xml::Dom::XmlNamedNodeMap^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlNamedNodeMap::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ UnwrapXmlNamedNodeMap(Local<Value> value) {
     return XmlNamedNodeMap::Unwrap<XmlNamedNodeMap>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlNamedNodeMap(Local<Object> exports) {
    XmlNamedNodeMap::Init(exports);
  }

  class XmlNodeList : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlNodeList").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "item", Item);
            Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
            Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
            Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
            Nan::SetPrototypeMethod(localRef, "first", First);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlNodeList").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlNodeList(::Windows::Data::Xml::Dom::XmlNodeList^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlNodeList^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlNodeList^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlNodeList *wrapperInstance = new XmlNodeList(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlNodeList^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlNodeList^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlNodeList(winRtInstance));
    }


    static void Item(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info.This())) {
        return;
      }

      XmlNodeList *wrapper = XmlNodeList::Unwrap<XmlNodeList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->Item(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info.This())) {
        return;
      }

      XmlNodeList *wrapper = XmlNodeList::Unwrap<XmlNodeList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IndexOf(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info.This())) {
        return;
      }

      XmlNodeList *wrapper = XmlNodeList::Unwrap<XmlNodeList>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          unsigned int arg1;
          
          bool result;
          result = wrapper->_instance->IndexOf(arg0, &arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Boolean>(result));
          Nan::Set(resObj, Nan::New<String>("index").ToLocalChecked(), Nan::New<Integer>(arg1));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetMany(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info.This())) {
        return;
      }

      XmlNodeList *wrapper = XmlNodeList::Unwrap<XmlNodeList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          ::Platform::Array<::Windows::Data::Xml::Dom::IXmlNode^>^ arg1 = ref new ::Platform::Array<::Windows::Data::Xml::Dom::IXmlNode^>(wrapper->_instance->Length - arg0);
          
          unsigned int result;
          result = wrapper->_instance->GetMany(arg0, arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("number").ToLocalChecked(), Nan::New<Integer>(result));
          Nan::Set(resObj, Nan::New<String>("items").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Data::Xml::Dom::IXmlNode^>::CreateArrayWrapper(arg1, 
            [](::Windows::Data::Xml::Dom::IXmlNode^ val) -> Local<Value> {
              return WrapIXmlNode(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(value);
            },
            [](Local<Value> value) -> ::Windows::Data::Xml::Dom::IXmlNode^ {
              return UnwrapIXmlNode(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info.This())) {
        return;
      }

      XmlNodeList *wrapper = XmlNodeList::Unwrap<XmlNodeList>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Data::Xml::Dom::IXmlNode^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Data::Xml::Dom::IXmlNode^>::CreateIteratorWrapper(result, 
            [](::Windows::Data::Xml::Dom::IXmlNode^ val) -> Local<Value> {
              return WrapIXmlNode(val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlNodeList^>(info.This())) {
        return;
      }

      XmlNodeList *wrapper = XmlNodeList::Unwrap<XmlNodeList>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlNodeList^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlNodeList(::Windows::Data::Xml::Dom::XmlNodeList^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlNodeList^ UnwrapXmlNodeList(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlNodeList::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlNodeList(::Windows::Data::Xml::Dom::XmlNodeList^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlNodeList::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlNodeList^ UnwrapXmlNodeList(Local<Value> value) {
     return XmlNodeList::Unwrap<XmlNodeList>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlNodeList(Local<Object> exports) {
    XmlNodeList::Init(exports);
  }

  class XmlProcessingInstruction : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlProcessingInstruction").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("target").ToLocalChecked(), TargetGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlProcessingInstruction").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlProcessingInstruction(::Windows::Data::Xml::Dom::XmlProcessingInstruction^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlProcessingInstruction^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlProcessingInstruction *wrapperInstance = new XmlProcessingInstruction(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlProcessingInstruction^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlProcessingInstruction(winRtInstance));
    }


    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Data = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void TargetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlProcessingInstruction^>(info.This())) {
        return;
      }

      XmlProcessingInstruction *wrapper = XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Target;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlProcessingInstruction(::Windows::Data::Xml::Dom::XmlProcessingInstruction^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ UnwrapXmlProcessingInstruction(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlProcessingInstruction::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlProcessingInstruction(::Windows::Data::Xml::Dom::XmlProcessingInstruction^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlProcessingInstruction::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlProcessingInstruction^ UnwrapXmlProcessingInstruction(Local<Value> value) {
     return XmlProcessingInstruction::Unwrap<XmlProcessingInstruction>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlProcessingInstruction(Local<Object> exports) {
    XmlProcessingInstruction::Init(exports);
  }

  class XmlText : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("XmlText").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "splitText", SplitText);
            Nan::SetPrototypeMethod(localRef, "substringData", SubstringData);
            Nan::SetPrototypeMethod(localRef, "appendData", AppendData);
            Nan::SetPrototypeMethod(localRef, "insertData", InsertData);
            Nan::SetPrototypeMethod(localRef, "deleteData", DeleteData);
            Nan::SetPrototypeMethod(localRef, "replaceData", ReplaceData);
            Nan::SetPrototypeMethod(localRef, "hasChildNodes", HasChildNodes);
            Nan::SetPrototypeMethod(localRef, "insertBefore", InsertBefore);
            Nan::SetPrototypeMethod(localRef, "replaceChild", ReplaceChild);
            Nan::SetPrototypeMethod(localRef, "removeChild", RemoveChild);
            Nan::SetPrototypeMethod(localRef, "appendChild", AppendChild);
            Nan::SetPrototypeMethod(localRef, "cloneNode", CloneNode);
            Nan::SetPrototypeMethod(localRef, "normalize", Normalize);
            Nan::SetPrototypeMethod(localRef, "selectSingleNode", SelectSingleNode);
            Nan::SetPrototypeMethod(localRef, "selectNodes", SelectNodes);
            Nan::SetPrototypeMethod(localRef, "selectSingleNodeNS", SelectSingleNodeNS);
            Nan::SetPrototypeMethod(localRef, "selectNodesNS", SelectNodesNS);
            Nan::SetPrototypeMethod(localRef, "getXml", GetXml);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefix").ToLocalChecked(), PrefixGetter, PrefixSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeValue").ToLocalChecked(), NodeValueGetter, NodeValueSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstChild").ToLocalChecked(), FirstChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastChild").ToLocalChecked(), LastChildGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespaceUri").ToLocalChecked(), NamespaceUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextSibling").ToLocalChecked(), NextSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeName").ToLocalChecked(), NodeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nodeType").ToLocalChecked(), NodeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ownerDocument").ToLocalChecked(), OwnerDocumentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("childNodes").ToLocalChecked(), ChildNodesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentNode").ToLocalChecked(), ParentNodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousSibling").ToLocalChecked(), PreviousSiblingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("innerText").ToLocalChecked(), InnerTextGetter, InnerTextSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("XmlText").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      XmlText(::Windows::Data::Xml::Dom::XmlText^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Data::Xml::Dom::XmlText^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info[0])) {
        try {
          winRtInstance = (::Windows::Data::Xml::Dom::XmlText^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      XmlText *wrapperInstance = new XmlText(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Data::Xml::Dom::XmlText^ winRtInstance;
      try {
        winRtInstance = (::Windows::Data::Xml::Dom::XmlText^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapXmlText(winRtInstance));
    }


    static void SplitText(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::IXmlText^ result;
          result = wrapper->_instance->SplitText(arg0);
          info.GetReturnValue().Set(WrapIXmlText(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SubstringData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->SubstringData(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->AppendData(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->InsertData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DeleteData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->DeleteData(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 3
        && info[0]->IsUint32()
        && info[1]->IsUint32()
        && info[2]->IsString())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          wrapper->_instance->ReplaceData(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasChildNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->HasChildNodes();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void InsertBefore(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->InsertBefore(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReplaceChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[1]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          ::Windows::Data::Xml::Dom::IXmlNode^ arg1 = UnwrapIXmlNode(info[1]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->ReplaceChild(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->RemoveChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AppendChild(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::IXmlNode^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::IXmlNode^ arg0 = UnwrapIXmlNode(info[0]);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->AppendChild(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->CloneNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Normalize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Normalize();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNode(arg0);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodes(arg0);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectSingleNodeNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::IXmlNode^ result;
          result = wrapper->_instance->SelectSingleNodeNS(arg0, arg1);
          info.GetReturnValue().Set(WrapIXmlNode(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SelectNodesNS(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          ::Windows::Data::Xml::Dom::XmlNodeList^ result;
          result = wrapper->_instance->SelectNodesNS(arg0, arg1);
          info.GetReturnValue().Set(WrapXmlNodeList(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetXml(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetXml();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Data = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Prefix;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrefixSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Prefix = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NodeValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NodeValue;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try {

        ::Platform::Object^ winRtValue = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->NodeValue = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->FirstChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastChildGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->LastChild;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NamespaceUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->NamespaceUri;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->NextSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NodeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NodeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::NodeType result = wrapper->_instance->NodeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNamedNodeMap^ result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(WrapXmlNamedNodeMap(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OwnerDocumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->OwnerDocument;
        info.GetReturnValue().Set(WrapXmlDocument(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChildNodesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::XmlNodeList^ result = wrapper->_instance->ChildNodes;
        info.GetReturnValue().Set(WrapXmlNodeList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ParentNodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->ParentNode;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousSiblingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        ::Windows::Data::Xml::Dom::IXmlNode^ result = wrapper->_instance->PreviousSibling;
        info.GetReturnValue().Set(WrapIXmlNode(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InnerText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InnerTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlText^>(info.This())) {
        return;
      }

      XmlText *wrapper = XmlText::Unwrap<XmlText>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->InnerText = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Data::Xml::Dom::XmlText^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapXmlText(::Windows::Data::Xml::Dom::XmlText^ wintRtInstance);
      friend ::Windows::Data::Xml::Dom::XmlText^ UnwrapXmlText(Local<Value> value);
  };

  Persistent<FunctionTemplate> XmlText::s_constructorTemplate;

  v8::Local<v8::Value> WrapXmlText(::Windows::Data::Xml::Dom::XmlText^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(XmlText::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Data::Xml::Dom::XmlText^ UnwrapXmlText(Local<Value> value) {
     return XmlText::Unwrap<XmlText>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitXmlText(Local<Object> exports) {
    XmlText::Init(exports);
  }


} } } } } 

NAN_MODULE_INIT(init) {
  // We ignore failures for now since it probably means that
  // the initialization already happened for STA, and that's cool

  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  /*
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  */

      NodeRT::Windows::Data::Xml::Dom::InitNodeTypeEnum(target);
      NodeRT::Windows::Data::Xml::Dom::InitDtdEntity(target);
      NodeRT::Windows::Data::Xml::Dom::InitDtdNotation(target);
      NodeRT::Windows::Data::Xml::Dom::InitIXmlCharacterData(target);
      NodeRT::Windows::Data::Xml::Dom::InitIXmlNode(target);
      NodeRT::Windows::Data::Xml::Dom::InitIXmlNodeSelector(target);
      NodeRT::Windows::Data::Xml::Dom::InitIXmlNodeSerializer(target);
      NodeRT::Windows::Data::Xml::Dom::InitIXmlText(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlAttribute(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlCDataSection(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlComment(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlDocument(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlDocumentFragment(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlDocumentType(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlDomImplementation(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlElement(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlEntityReference(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlLoadSettings(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlNamedNodeMap(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlNodeList(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlProcessingInstruction(target);
      NodeRT::Windows::Data::Xml::Dom::InitXmlText(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Data.Xml.Dom", target);
}



NODE_MODULE(binding, init)
