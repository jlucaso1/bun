/*
 * Copyright (c) 2015 Igalia
 * Copyright (c) 2015 Igalia S.L.
 * Copyright (c) 2015 Igalia.
 * Copyright (c) 2015, 2016 Canon Inc. All rights reserved.
 * Copyright (c) 2015, 2016, 2017 Canon Inc.
 * Copyright (c) 2016, 2020 Apple Inc. All rights reserved.
 * Copyright (c) 2022 Codeblog Corp. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

// DO NOT EDIT THIS FILE. It is automatically generated from JavaScript files for
// builtins by the script: Source/JavaScriptCore/Scripts/generate-js-builtins.py

#include "config.h"
#include "NodeEventsBuiltins.h"

#include "WebCoreJSClientData.h"
#include <JavaScriptCore/HeapInlines.h>
#include <JavaScriptCore/IdentifierInlines.h>
#include <JavaScriptCore/ImplementationVisibility.h>
#include <JavaScriptCore/Intrinsic.h>
#include <JavaScriptCore/JSCJSValueInlines.h>
#include <JavaScriptCore/JSCellInlines.h>
#include <JavaScriptCore/StructureInlines.h>
#include <JavaScriptCore/VM.h>

namespace WebCore {

const JSC::ConstructAbility s_nodeEventsOnAsyncIteratorCodeConstructAbility = JSC::ConstructAbility::CannotConstruct;
const JSC::ConstructorKind s_nodeEventsOnAsyncIteratorCodeConstructorKind = JSC::ConstructorKind::None;
const JSC::ImplementationVisibility s_nodeEventsOnAsyncIteratorCodeImplementationVisibility = JSC::ImplementationVisibility::Public;
const int s_nodeEventsOnAsyncIteratorCodeLength = 4473;
static const JSC::Intrinsic s_nodeEventsOnAsyncIteratorCodeIntrinsic = JSC::NoIntrinsic;
const char* const s_nodeEventsOnAsyncIteratorCode =
    "(function (emitter, event, options) {\n" \
    "  \"use strict\";\n" \
    "\n" \
    "  var { AbortSignal, Number, Error } = globalThis;\n" \
    "\n" \
    "  var AbortError = class AbortError extends Error {\n" \
    "    constructor(message = \"The operation was aborted\", options = void 0) {\n" \
    "      if (options !== void 0 && typeof options !== \"object\") {\n" \
    "        throw new Error(`Invalid AbortError options:\\n" \
    "\\n" \
    "${JSON.stringify(options, null, 2)}`);\n" \
    "      }\n" \
    "      super(message, options);\n" \
    "      this.code = \"ABORT_ERR\";\n" \
    "      this.name = \"AbortError\";\n" \
    "    }\n" \
    "  };\n" \
    "\n" \
    "  if (@isUndefinedOrNull(emitter)) @throwTypeError(\"emitter is required\");\n" \
    "  //\n" \
    "  if (!(typeof emitter === \"object\" && @isCallable(emitter.emit) && @isCallable(emitter.on)))\n" \
    "    @throwTypeError(\"emitter must be an EventEmitter\");\n" \
    "\n" \
    "  if (@isUndefinedOrNull(options)) options = {};\n" \
    "\n" \
    "  //\n" \
    "  var signal = options.signal;\n" \
    "  if (!@isUndefinedOrNull(signal) && !(signal instanceof AbortSignal))\n" \
    "    @throwTypeError(\"options.signal must be an AbortSignal\");\n" \
    "\n" \
    "  if (signal?.aborted) {\n" \
    "    //\n" \
    "    throw new AbortError(@undefined, { cause: signal?.reason });\n" \
    "  }\n" \
    "\n" \
    "  var highWatermark = options.highWatermark ?? Number.MAX_SAFE_INTEGER;\n" \
    "  if (highWatermark < 1) \n" \
    "    @throwRangeError(\"options.highWatermark must be >= 1\");\n" \
    "\n" \
    "  var lowWatermark = options.lowWatermark ?? 1;\n" \
    "  if (lowWatermark < 1) \n" \
    "    @throwRangeError(\"options.lowWatermark must be >= 1\");\n" \
    "\n" \
    "  var unconsumedEvents = @createFIFO();\n" \
    "  var unconsumedPromises = @createFIFO();\n" \
    "\n" \
    "  var paused = false;\n" \
    "  var error = null;\n" \
    "  var finished = false;\n" \
    "  var size = 0;\n" \
    "  var listeners = [];\n" \
    "\n" \
    "  function abortListener() {\n" \
    "    errorHandler(new AbortError(@undefined, { cause: signal?.reason }));\n" \
    "  }\n" \
    "\n" \
    "  function eventHandler(value) {\n" \
    "    if (unconsumedPromises.isEmpty()) {\n" \
    "      size++;\n" \
    "      if (!paused && size > highWatermark) {\n" \
    "        paused = true;\n" \
    "        emitter.pause();\n" \
    "      }\n" \
    "      unconsumedEvents.push(value);\n" \
    "    } else unconsumedPromises.shift().@resolve.@call(@undefined, [value]);\n" \
    "  }\n" \
    "\n" \
    "  function closeHandler() {\n" \
    "    removeAllListeners(listeners);\n" \
    "    finished = true;\n" \
    "    while (!unconsumedPromises.isEmpty()) {\n" \
    "      const promise = unconsumedPromises.shift();\n" \
    "      promise.@resolve.@call(@undefined, [@undefined]);\n" \
    "    }\n" \
    "    return @createFulfilledPromise([@undefined]);\n" \
    "  }\n" \
    "\n" \
    "  function errorHandler(err) {\n" \
    "    if (unconsumedPromises.isEmpty()) error = err;\n" \
    "    else unconsumedPromises.shift().@reject.@call(@undefined, err);\n" \
    "  \n" \
    "    closeHandler();\n" \
    "  }\n" \
    "  \n" \
    "  function addEventListener(emitter, event, handler) {\n" \
    "    emitter.on(event, handler);\n" \
    "    listeners.push([emitter, event, handler]);\n" \
    "  }\n" \
    "  \n" \
    "  function removeAllListeners() {\n" \
    "    while (listeners.length > 0) {\n" \
    "      var entry = listeners.pop();\n" \
    "      var [emitter, event, handler] = entry;\n" \
    "      emitter.off(event, handler);\n" \
    "    }\n" \
    "  }\n" \
    "\n" \
    "  var createIterator = async function* NodeEventsOnAsyncIterator() {\n" \
    "    //\n" \
    "    try {\n" \
    "      while (true) {\n" \
    "        //\n" \
    "        while (size) {\n" \
    "          const value = unconsumedEvents.shift();\n" \
    "          size--;\n" \
    "          if (paused && size < lowWatermark) {\n" \
    "            emitter.resume();\n" \
    "            paused = false;\n" \
    "            break;\n" \
    "          }\n" \
    "          yield @createFulfilledPromise([value]);\n" \
    "        }\n" \
    "\n" \
    "        //\n" \
    "        //\n" \
    "        //\n" \
    "        if (error) {\n" \
    "          throw error;\n" \
    "        }\n" \
    "\n" \
    "        //\n" \
    "        if (finished) break;\n" \
    "\n" \
    "        //\n" \
    "        var nextEventPromiseCapability = @newPromiseCapability(@Promise);\n" \
    "        unconsumedPromises.push(nextEventPromiseCapability);\n" \
    "        yield nextEventPromiseCapability.@promise;\n" \
    "      }\n" \
    "    } finally {\n" \
    "      closeHandler();\n" \
    "    }\n" \
    "  };\n" \
    "\n" \
    "  //\n" \
    "  addEventListener(emitter, event, eventHandler);\n" \
    "  if (event !== \"error\" && typeof emitter.on === \"function\") {\n" \
    "    addEventListener(emitter, \"error\", errorHandler);\n" \
    "  }\n" \
    "  var closeEvents = options?.close;\n" \
    "  if (closeEvents?.length) {\n" \
    "    for (var i = 0; i < closeEvents.length; i++) {\n" \
    "      addEventListener(emitter, closeEvents[i], closeHandler);\n" \
    "    }\n" \
    "  }\n" \
    "\n" \
    "  if (signal)\n" \
    "    signal.once(\"abort\", abortListener);\n" \
    "\n" \
    "  var iterator = createIterator();\n" \
    "\n" \
    "  @Object.defineProperties(iterator, {\n" \
    "    return: {\n" \
    "      value: function() {\n" \
    "        return closeHandler();\n" \
    "      },\n" \
    "    },\n" \
    "    throw: {\n" \
    "      value: function(err) {\n" \
    "        if (!err || !(err instanceof Error)) {\n" \
    "          throw new TypeError(\"EventEmitter.AsyncIterator must be called with an error\");\n" \
    "        }\n" \
    "        errorHandler(err);\n" \
    "      },\n" \
    "    },\n" \
    "    [Symbol.asyncIterator]: {\n" \
    "      value: function() { return this; }\n" \
    "    },\n" \
    "  });\n" \
    "  return iterator;\n" \
    "})\n" \
;


#define DEFINE_BUILTIN_GENERATOR(codeName, functionName, overriddenName, argumentCount) \
JSC::FunctionExecutable* codeName##Generator(JSC::VM& vm) \
{\
    JSVMClientData* clientData = static_cast<JSVMClientData*>(vm.clientData); \
    return clientData->builtinFunctions().nodeEventsBuiltins().codeName##Executable()->link(vm, nullptr, clientData->builtinFunctions().nodeEventsBuiltins().codeName##Source(), std::nullopt, s_##codeName##Intrinsic); \
}
WEBCORE_FOREACH_NODEEVENTS_BUILTIN_CODE(DEFINE_BUILTIN_GENERATOR)
#undef DEFINE_BUILTIN_GENERATOR


} // namespace WebCore
