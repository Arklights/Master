//--------------------------------------------------------------------------
// Copyright (C) 2014-2017 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------
// http_inspect.h author Tom Peters <thopeter@cisco.com>

#ifndef HTTP_INSPECT_H
#define HTTP_INSPECT_H

//-------------------------------------------------------------------------
// HttpInspect class
//-------------------------------------------------------------------------

#include "http_enum.h"
#include "http_field.h"
#include "http_module.h"
#include "http_msg_section.h"
#include "http_stream_splitter.h"
#include "log/messages.h"

class HttpApi;

class HttpInspect : public Inspector
{
public:
    HttpInspect(const HttpParaList* params_);
    ~HttpInspect() override { delete params; }

    bool get_buf(InspectionBuffer::Type ibt, Packet* p, InspectionBuffer& b) override;
    bool get_buf(unsigned id, Packet* p, InspectionBuffer& b) override;
    bool http_get_buf(
        unsigned id, uint64_t sub_id, uint64_t form, Packet* p, InspectionBuffer& b);
    bool get_fp_buf(InspectionBuffer::Type ibt, Packet* p, InspectionBuffer& b) override;
    bool configure(SnortConfig*) override;
    void show(SnortConfig*) override { LogMessage("HttpInspect\n"); }
    void eval(Packet* p) override;
    void clear(Packet* p) override;
    void tinit() override { }
    void tterm() override { }
    HttpStreamSplitter* get_splitter(bool is_client_to_server) override
    {
        return new HttpStreamSplitter(is_client_to_server, this);
    }
    static HttpEnums::InspectSection get_latest_is(const Packet* p);

    // Callbacks that provide "extra data"
    static int get_xtra_trueip(Flow*, uint8_t**, uint32_t*, uint32_t*);
    static int get_xtra_uri(Flow*, uint8_t**, uint32_t*, uint32_t*);
    static int get_xtra_host(Flow*, uint8_t** buf, uint32_t* len, uint32_t* type);
    static int get_xtra_jsnorm(Flow*, uint8_t**, uint32_t*, uint32_t*);

private:
    friend HttpApi;
    friend HttpStreamSplitter;

    bool process(const uint8_t* data, const uint16_t dsize, Flow* const flow,
        HttpEnums::SourceId source_id_, bool buf_owner) const;
    static HttpEnums::SourceId get_latest_src(const Packet* p);

    const HttpParaList* const params;

    // Registrations for "extra data"
    static uint32_t xtra_trueip_id;
    static uint32_t xtra_uri_id;
    static uint32_t xtra_host_id;
    static uint32_t xtra_jsnorm_id;
};

#endif

