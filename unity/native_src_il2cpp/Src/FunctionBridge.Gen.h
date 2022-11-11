﻿//生成规则
//1、js传到c#：JsValueToCSObject，如果后续要性能，可以考虑根据类型预计算，按值类型，object，其它普通类等分好类。
//2、除object类型以外对于this不检查（GetPointerFast）直接获取指针，包括值类型和引用类型，而object几个方法特殊处理，用JsValueToCSObject
//3、值类型传到js：CopyValueType
//4、除object以外的引用类型传到js：CSRefToJsValue
//5、object类型传到js：CSAnyToJsValue
//6、out、ref、指针都在原有类型基础上加指针，比如ref int是int32_t *，out Vector是s_r4r4r4_*， ref object是void**
//7、TODO：处理rawobject？
//8、c#结构体要生成对应的c++结构体（之前碰到浮点和整数存放的寄存器不一样导致的脏数据问题）

struct s_r4r4r4_
{
    float f0;
    float f1;
    float f2;
};

struct s_r4r4r4r4_
{
    float f0;
    float f1;
    float f2;
    float f3;
};

//typedef int32_t (*FunctionPointerType) (void*, int32_t, int32_t, const RuntimeMethod*);
static int32_t b_i4i4i4(void* object, int32_t p1, int32_t p2, void* method)
{
    PersistentObjectInfo* delegateInfo = GetObjectData(object, PersistentObjectInfo);
    if (delegateInfo->JsEnvLifeCycleTracker.expired())
    {
        GUnityExports.ThrowInvalidOperationException("JsEnv had been destroy");
        return {};
    }
    //PLog("p1=%d, p2=%d", p1, p2);
    //PLog("delegate invoke: a=%d, b=%d, c=%d, d=%d, e=%d, p1=%d, p2=%d", delegateInfo->a, delegateInfo->b, delegateInfo->c, delegateInfo->d, delegateInfo->e, p1, p2);
    v8::Isolate* Isolate = delegateInfo->Isolate;
    v8::Isolate::Scope IsolateScope(Isolate);
    v8::HandleScope HandleScope(Isolate);
    auto Context = delegateInfo->Context.Get(Isolate);
    v8::Context::Scope ContextScope(Context);

    v8::TryCatch TryCatch(Isolate);
    auto Function = delegateInfo->JsObject.Get(Isolate).As<v8::Function>();
    v8::Local<v8::Value> Argv[2]{v8::Integer::New(Isolate, p1), v8::Integer::New(Isolate, p2)};
    auto MaybeRet = Function->Call(Context, v8::Undefined(Isolate), 2, Argv);
    
    if (TryCatch.HasCaught())
    {
        auto msg = DataTransfer::ExceptionToString(Isolate, TryCatch.Exception());
        GUnityExports.ThrowInvalidOperationException(msg.c_str());
        return {};
    }

    if (!MaybeRet.IsEmpty())
    {
        return MaybeRet.ToLocalChecked()->Int32Value(Context).ToChecked();
    }
    
    return {};
}

static BridgeFuncInfo g_bridgeFuncInfos[] = {
    {"i4i4i4", (MethodPointer)b_i4i4i4},
    {nullptr, nullptr}    
};


static bool w_i4i4i4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    if (checkArgument)
    {
        if (!Info[0]->IsNumber()) return false;
        if (!Info[1]->IsNumber()) return false;
    }
    auto a = Info[0]->Int32Value(Context).ToChecked();
    auto b = Info[1]->Int32Value(Context).ToChecked();
    typedef int32_t (*NativeFuncPtr)(int32_t ___a0, int32_t ___b1, const void* method);
    
    int32_t ret = ((NativeFuncPtr)methodPointer)(a, b, method);
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_vt(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    if (checkArgument)
    {
        if (Info.Length() != 0) return false;
    }
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    
    typedef void (*NativeFuncPtr)(void* ___p1, const void* method);
    
    ((NativeFuncPtr)methodPointer)(This, method);
    return true;
}

static bool w_vtr4r4r4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    
    auto p0 = (float)Info[0]->NumberValue(Context).ToChecked();
    auto p1 = (float)Info[1]->NumberValue(Context).ToChecked();
    auto p2 = (float)Info[2]->NumberValue(Context).ToChecked();
    
    typedef void (*NativeFuncPtr)(void* ___this, float ___p0, float ___p1, float ___p2, const void* method);
    
    ((NativeFuncPtr)methodPointer)(This, p0, p1, p2, method);
    return true;
}

static bool w_vs_r4r4r4_(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    //TODO: 如果传错参数，ToLocalChecked会abort，应该做个检查
    auto p0 = puerts::DataTransfer::GetPointerFast<s_r4r4r4_>(Info[0]->ToObject(Context).ToLocalChecked());
    
    typedef void (*NativeFuncPtr)( s_r4r4r4_ p0, const void* method);
    
    ((NativeFuncPtr)methodPointer)(*p0, method);
    return true;
}


static bool w_i4ti4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    if (checkArgument)
    {
        if (!Info[0]->IsNumber()) return false;
    }
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    auto p1 = Info[0]->Int32Value(Context).ToChecked();
    
    typedef int32_t (*NativeFuncPtr)(void* ___this, int32_t ___b1, const void* method);
    
    int32_t ret = ((NativeFuncPtr)methodPointer)(This, p1, method);
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_s_r4r4r4_ts_r4r4r4_(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    if (checkArgument)
    {
        //TODO: check type_id
        if (!Info[0]->IsObject()) return false;
    }
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    auto p1 = puerts::DataTransfer::GetPointerFast<s_r4r4r4_>(Info[0]->ToObject(Context).ToLocalChecked());
    
    typedef s_r4r4r4_ (*NativeFuncPtr)(void* ___this, s_r4r4r4_ p0 , const void* method);
    
    auto obj = ((NativeFuncPtr)methodPointer)(This, *p1, method);
    void* klass = typeInfos[0];
    //void* buff =  GUnityExports.ObjectAllocate(klass); //TODO: allc by jsenv
    //memcpy(buff, &obj, sizeof(obj));
    //auto ret = DataTransfer::FindOrAddCData(Isolate, Context, klass, buff, false);
    auto ret = CopyValueType(Isolate, Context, klass, &obj, sizeof(obj));
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_vto(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    
    //auto p1 = puerts::DataTransfer::GetPointer<void>(Context, Info[0]);
    //auto klass1 = puerts::DataTransfer::GetPointer<void>(Context, Info[0], 1);
    //p1 = GUnityExports.IsInst(p1, typeInfos[0]);
    auto p1 = JsValueToCSRef(Context, Info[0], typeInfos[0]);
    
    typedef void (*NativeFuncPtr)(void* ___this, void* ___p1, const void* __method);
    
    ((NativeFuncPtr)methodPointer)(This, p1, method);
    return true;
}

static bool w_vti4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    auto p1 = Info[0]->Int32Value(Context).ToChecked();
    
    typedef void (*NativeFuncPtr)(void* ___this, int32_t ___b1, const void* method);
    
    ((NativeFuncPtr)methodPointer)(This, p1, method);
    return true;
}

static bool w_i4t(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    
    typedef int32_t (*NativeFuncPtr)(void* ___this, const void* method);
    
    auto ret = ((NativeFuncPtr)methodPointer)(This, method);
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_vr4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto p0 = (float)Info[0]->NumberValue(Context).ToChecked();
    
    typedef void (*NativeFuncPtr)(float ___b1, const void* method);
    
    ((NativeFuncPtr)methodPointer)(p0, method);
    return true;
}

static bool w_r4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    
    typedef float (*NativeFuncPtr)(const void* method);
    
    auto ret = ((NativeFuncPtr)methodPointer)(method);
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_vti4i4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    if (checkArgument)
    {
        //PLog("w_vti4i4 %d %d %d", Info.Length(), Info[0]->IsNumber(), Info[1]->IsNumber());
        if (Info.Length() != 2) return false;
        if (!Info[0]->IsNumber()) return false;
        if (!Info[1]->IsNumber()) return false;
    }
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    auto p1 = Info[0]->Int32Value(Context).ToChecked();
    auto p2 = Info[1]->Int32Value(Context).ToChecked();
    
    typedef void (*NativeFuncPtr)(void* ___this, int32_t ___b1, int32_t ___b2, const void* method);
    
    ((NativeFuncPtr)methodPointer)(This, p1, p2, method);
    return true;
}

static bool w_i4ti4i4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    if (checkArgument)
    {
        //PLog("w_vti4i4 %d %d %d", Info.Length(), Info[0]->IsNumber(), Info[1]->IsNumber());
        if (Info.Length() != 2) return false;
        if (!Info[0]->IsNumber()) return false;
        if (!Info[1]->IsNumber()) return false;
    }
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    auto p1 = Info[0]->Int32Value(Context).ToChecked();
    auto p2 = Info[1]->Int32Value(Context).ToChecked();
    
    typedef int32_t (*NativeFuncPtr)(void* ___this, int32_t ___b1, int32_t ___b2, const void* method);
    
    auto ret = ((NativeFuncPtr)methodPointer)(This, p1, p2, method);
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_o(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    typedef void* (*NativeFuncPtr)(const void* method);
    
    void* obj =((NativeFuncPtr)methodPointer)(method);
    
    void* klass = *reinterpret_cast<void**>(obj);
    
    auto ret = DataTransfer::FindOrAddCData(Isolate, Context, klass, obj, true);
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_s_r4r4r4_(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    typedef s_r4r4r4_ (*NativeFuncPtr)(const void* method);
    
    auto obj =((NativeFuncPtr)methodPointer)(method);
    void* klass = typeInfos[0];
    
    //v8::Local<v8::ArrayBuffer> ab = v8::ArrayBuffer::New(Isolate, sizeof(obj)); //puerts VecRet using 16446
    //void* buff = ab->GetBackingStore()->Data();
    //uint8_t* buff = new uint8_t[sizeof(obj)]; // puerts VecRet using 4481
    
    auto ret = CopyValueType(Isolate, Context, klass, &obj, sizeof(obj));
    
    //ret.As<v8::Object>()->Set(Context, 0, ab);
    
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_s_r4r4r4r4_(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    typedef s_r4r4r4r4_ (*NativeFuncPtr)(const void* method);
    
    auto obj =((NativeFuncPtr)methodPointer)(method);
    void* klass = typeInfos[0];
    
    //v8::Local<v8::ArrayBuffer> ab = v8::ArrayBuffer::New(Isolate, sizeof(obj)); //puerts VecRet using 16446
    //void* buff = ab->GetBackingStore()->Data();
    //uint8_t* buff = new uint8_t[sizeof(obj)]; // puerts VecRet using 4481
    
    void* buff =  GUnityExports.ObjectAllocate(klass); //TODO: allc by jsenv
    
    memcpy(buff, &obj, sizeof(obj));
    //auto ret = v8::Object::New(Isolate);
    auto ret = DataTransfer::FindOrAddCData(Isolate, Context, nullptr, buff, false);
    GUnityExports.ValueTypeDeallocate(buff);
    
    //ret.As<v8::Object>()->Set(Context, 0, ab);
    
    Info.GetReturnValue().Set(ret);
    return true;
}

static bool w_os(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    v8::String::Utf8Value s(Isolate, Info[0]);
    
    auto p1 = GUnityExports.CStringToCSharpString(*s);
    
    typedef void* (*NativeFuncPtr)(void* p, const void* method);
    
    void* obj =((NativeFuncPtr)methodPointer)(p1, method);
    
    Info.GetReturnValue().Set(CSRefToJsValue(Isolate, Context, obj));
    return true;
}

static bool w_ots(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    v8::String::Utf8Value s(Isolate, Info[0]);
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    
    auto p1 = GUnityExports.CStringToCSharpString(*s);
    
    typedef void* (*NativeFuncPtr)(void* ___this, void* p, const void* method);
    
    void* obj =((NativeFuncPtr)methodPointer)(This, p1, method);
    
    Info.GetReturnValue().Set(CSRefToJsValue(Isolate, Context, obj));
    return true;
}

static bool w_vtPi4(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    auto p1 = 0;
    v8::Local<v8::Object> Outer;
    if (Info[0]->IsObject())
    {
        Outer = Info[0]->ToObject(Context).ToLocalChecked();
        auto Realvalue = Outer->Get(Context, 0).ToLocalChecked();
        p1 = Realvalue->Int32Value(Context).ToChecked();
    }
    
    typedef void (*NativeFuncPtr)(void* ___this, int32_t* ___b1, const void* method);
    
    ((NativeFuncPtr)methodPointer)(This, &p1, method);
    
    if (!Outer.IsEmpty())
    {
        Outer->Set(Context, 0, v8::Integer::New(Isolate, p1));
    }
    
    return true;
}

static bool w_vtPO(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    void* p1 = nullptr;
    v8::Local<v8::Object> Outer;
    if (Info[0]->IsObject())
    {
        Outer = Info[0]->ToObject(Context).ToLocalChecked();
        auto Realvalue = Outer->Get(Context, 0).ToLocalChecked();
        p1 = JsValueToCSRef(Context, Realvalue, typeInfos[0]);
    }
    
    typedef void (*NativeFuncPtr)(void* ___this, void ** ___p1, const void* method);
    
    ((NativeFuncPtr)methodPointer)(This, &p1, method);
    
    if (!Outer.IsEmpty())
    {
        Outer->Set(Context, 0, CSAnyToJsValue(Isolate, Context, p1));
    }
    
    return true;
}

//for System.Type ToString
static bool w_sT(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto ThisType = GetTypeId(Info.Holder());
    auto This = JsValueToCSRef(Context, Info.Holder(), ThisType);
    typedef void* (*NativeFuncPtr)(void* ___this, const void* method);
    auto ret = ((NativeFuncPtr)methodPointer)(This, method);
    if (ret)
    {
        Info.GetReturnValue().Set(CSAnyToJsValue(Isolate, Context, ret));
    }
    return true;
}

// any type but System.Type ToString
static bool w_st(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto This = puerts::DataTransfer::GetPointerFast<void>(Info.Holder());
    
    typedef void* (*NativeFuncPtr)(void* ___this, const void* method);
    auto ret = ((NativeFuncPtr)methodPointer)(This, method);
    if (ret)
    {
        Info.GetReturnValue().Set(CSAnyToJsValue(Isolate, Context, ret));
    }
    return true;
}

static bool w_vO(void* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& Info, bool checkArgument, void** typeInfos) {
    v8::Isolate* Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    
    auto p1 = JsValueToCSRef(Context, Info[0], typeInfos[0]);
    
    typedef void (*NativeFuncPtr)(void* ___p1, const void* __method);
    
    ((NativeFuncPtr)methodPointer)(p1, method);
    return true;
}

static WrapFuncInfo g_wrapFuncInfos[] = {
    {"i4i4i4", w_i4i4i4},
    {"vt", w_vt},
    {"i4ti4", w_i4ti4},
    {"s_r4r4r4_ts_r4r4r4_", w_s_r4r4r4_ts_r4r4r4_},
    {"vs_r4r4r4_", w_vs_r4r4r4_},
    {"vtr4r4r4", w_vtr4r4r4},
    {"vto", w_vto},
    {"vti4", w_vti4},
    {"vr4", w_vr4},
    {"r4", w_r4},
    {"i4t", w_i4t},
    {"vti4i4", w_vti4i4},
    {"o", w_o},
    {"s_r4r4r4_", w_s_r4r4r4_},
    {"s_r4r4r4r4_", w_s_r4r4r4r4_},
    {"i4ti4i4", w_i4ti4i4},
    {"os", w_os},
    {"ots", w_ots},
    {"vtPi4", w_vtPi4},
    {"vtPO", w_vtPO},
    {"sT", w_sT},
    {"st", w_st},
    {"vO", w_vO},
    {nullptr, nullptr}
};

static void ifg_ti4(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    
    int32_t __ret;
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    GUnityExports.FieldGet(__this, fieldInfo, offset, &__ret);
    
    info.GetReturnValue().Set(__ret);
}

static void ifs_ti4(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    auto __p1 = info[0]->Int32Value(context).ToChecked();
    GUnityExports.FieldSet(__this, fieldInfo, offset, &__p1);
}

static void ifg_tr4(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    float __ret;
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    GUnityExports.FieldGet(__this, fieldInfo, offset, &__ret);
    
    //PLog("get float %p %d %f", __this, offset, __ret);
    
    info.GetReturnValue().Set(__ret);
}

static void ifs_tr4(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    auto __p1 = (float)info[0]->NumberValue(context).ToChecked();
    //PLog("set float %p %d %f", __this, offset, __p1);
    GUnityExports.FieldSet(__this, fieldInfo, offset, &__p1);
}

static void ifg_ts_r4r4r4_(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    auto __ptr = (char*)__this + offset;
    
    auto __ret = DataTransfer::FindOrAddCData(isolate, context, typeInfo, __ptr, true);

    info.GetReturnValue().Set(__ret);
}

static void ifs_ts_r4r4r4_(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    auto __p1 = puerts::DataTransfer::GetPointerFast<s_r4r4r4_>(info[0]->ToObject(context).ToLocalChecked());
    GUnityExports.FieldSet(__this, fieldInfo, offset, __p1);
}

static void ifg_s_r4r4r4_(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto ptr = GUnityExports.GetValueTypeFieldPtr(nullptr, fieldInfo, offset);
    auto ret = DataTransfer::FindOrAddCData(isolate, context, typeInfo, ptr, true);

    info.GetReturnValue().Set(ret);
}

static void ifs_s_r4r4r4_(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __p1 = puerts::DataTransfer::GetPointerFast<s_r4r4r4_>(info[0]->ToObject(context).ToLocalChecked());
    GUnityExports.FieldSet(nullptr, fieldInfo, offset, __p1);
}

static void ifg_r4(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    float __ret;
    
    GUnityExports.FieldGet(nullptr, fieldInfo, offset, &__ret);
    
    //PLog("get float %p %d %f", __this, offset, __ret);
    
    info.GetReturnValue().Set(__ret);
}

static void ifs_r4(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __p1 = (float)info[0]->NumberValue(context).ToChecked();
    //PLog("set float %p %d %f", __this, offset, __p1);
    GUnityExports.FieldSet(nullptr, fieldInfo, offset, &__p1);
}

static void ifg_to(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    void* obj;
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    GUnityExports.FieldGet(__this, fieldInfo, offset, &obj);
    
    void* klass = *reinterpret_cast<void**>(obj);
    
    auto ret = DataTransfer::FindOrAddCData(isolate, context, klass, obj, true);
    info.GetReturnValue().Set(ret);
}

static void ifs_to(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    auto __this = puerts::DataTransfer::GetPointerFast<void>(info.Holder());
    auto __p1 = puerts::DataTransfer::GetPointerFast<void>(info[0]->ToObject(context).ToLocalChecked());
    //PLog("set float %p %d %f", __this, offset, __p1);
    GUnityExports.FieldSet(__this, fieldInfo, offset, &__p1);
}

static FieldWrapFuncInfo g_fieldWrapFuncInfos[] = {
    {"ti4", ifg_ti4, ifs_ti4},
    {"tr4", ifg_tr4, ifs_tr4},
    {"ts_r4r4r4_", ifg_ts_r4r4r4_, ifs_ts_r4r4r4_},
    {"s_r4r4r4_", ifg_s_r4r4r4_, ifs_s_r4r4r4_},
    {"r4", ifg_r4, ifs_r4},
    {"to", ifg_to, ifs_to},
    {nullptr, nullptr, nullptr}    
};
