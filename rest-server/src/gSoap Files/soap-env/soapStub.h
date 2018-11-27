/* soapStub.h
   Generated by gSOAP 2.8.28 from soap-envelope.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include <deque>
#include <list>
#include <vector>
#include <set>
#define SOAP_NAMESPACE_OF_ns1	"http://www.w3.org/2001/12/soap-envelope"

#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#if GSOAP_VERSION != 20828
# error "GSOAP VERSION 20828 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE_xsd__QName
#define SOAP_TYPE_xsd__QName (15)
typedef std::string xsd__QName;
#endif


/******************************************************************************\
 *                                                                            *
 * Classes, Structs, and Unions                                               *
 *                                                                            *
\******************************************************************************/

struct SOAP_ENV__Envelope;	/* soap-envelope.h:139 */
class ns1__Envelope;	/* soap-envelope.h:165 */
class ns1__Header;	/* soap-envelope.h:168 */
class ns1__Body;	/* soap-envelope.h:171 */
class ns1__Fault;	/* soap-envelope.h:174 */
class ns1__detail;	/* soap-envelope.h:177 */

/* soap-envelope.h:139 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (30)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 30; } /* = unique type id SOAP_TYPE_SOAP_ENV__Header */
	         SOAP_ENV__Header();
	friend SOAP_FMAC1 SOAP_ENV__Header * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* soap-envelope.h:139 */
#ifndef SOAP_TYPE_SOAP_ENV__Envelope
#define SOAP_TYPE_SOAP_ENV__Envelope (11)
/* SOAP-ENV:Envelope complex type: */
struct SOAP_ENV__Envelope
{
public:
	struct SOAP_ENV__Header *SOAP_ENV__Header;	/* optional element of XSD type SOAP-ENV:Header */
	char *SOAP_ENV__Body;	/* optional element of XSD type xsd:anyType */
public:
	int soap_type() const { return 11; } /* = unique type id SOAP_TYPE_SOAP_ENV__Envelope */
	         SOAP_ENV__Envelope();
	friend SOAP_FMAC1 SOAP_ENV__Envelope * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Envelope(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* soap-envelope.h:165 */
#ifndef SOAP_TYPE_ns1__Envelope
#define SOAP_TYPE_ns1__Envelope (19)
/* ns1:Envelope complex type: */
class SOAP_CMAC ns1__Envelope
{
public:
	struct SOAP_ENV__Header *SOAP_ENV__Header;	/* optional element of XSD type SOAP-ENV:Header */
	std::string SOAP_ENV__Body_;	/* required element of XSD type SOAP-ENV:Body */
	char *__anyAttribute;	/* optional attribute of XSD type xsd:anyType */
	struct soap *soap;	/* transient (not serialized) */
public:
	/// Return the unique type ID value SOAP_TYPE_ns1__Envelope (19)
	virtual int soap_type(void) const { return 19; }
	/// Set object's data members to default values
	virtual void soap_default(struct soap*);
	/// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
	virtual void soap_serialize(struct soap*) const;
	/// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
	virtual int soap_put(struct soap*, const char *tag, const char *type) const;
	/// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
	virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
	/// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
	virtual void *soap_get(struct soap*, const char *tag, const char *type);
	/// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
	virtual void *soap_in(struct soap*, const char *tag, const char *type);
	/// Return a new object of type ns1__Envelope, default initialized and not managed by a soap context
	virtual ns1__Envelope *soap_alloc(void) const { return SOAP_NEW(ns1__Envelope); }
	         ns1__Envelope() { ns1__Envelope::soap_default(NULL); }
	virtual ~ns1__Envelope() { }
	friend SOAP_FMAC1 ns1__Envelope * SOAP_FMAC2 soap_instantiate_ns1__Envelope(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* soap-envelope.h:168 */
#ifndef SOAP_TYPE_ns1__Header
#define SOAP_TYPE_ns1__Header (20)
/* ns1:Header complex type: */
class SOAP_CMAC ns1__Header
{
public:
	std::vector<char *> __any;
	char *__anyAttribute;	/* optional attribute of XSD type xsd:anyType */
	struct soap *soap;	/* transient (not serialized) */
public:
	/// Return the unique type ID value SOAP_TYPE_ns1__Header (20)
	virtual int soap_type(void) const { return 20; }
	/// Set object's data members to default values
	virtual void soap_default(struct soap*);
	/// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
	virtual void soap_serialize(struct soap*) const;
	/// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
	virtual int soap_put(struct soap*, const char *tag, const char *type) const;
	/// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
	virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
	/// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
	virtual void *soap_get(struct soap*, const char *tag, const char *type);
	/// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
	virtual void *soap_in(struct soap*, const char *tag, const char *type);
	/// Return a new object of type ns1__Header, default initialized and not managed by a soap context
	virtual ns1__Header *soap_alloc(void) const { return SOAP_NEW(ns1__Header); }
	         ns1__Header() { ns1__Header::soap_default(NULL); }
	virtual ~ns1__Header() { }
	friend SOAP_FMAC1 ns1__Header * SOAP_FMAC2 soap_instantiate_ns1__Header(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* soap-envelope.h:171 */
#ifndef SOAP_TYPE_ns1__Body
#define SOAP_TYPE_ns1__Body (21)
/* ns1:Body complex type: */
class SOAP_CMAC ns1__Body
{
public:
	std::vector<char *> __any;
	char *__anyAttribute;	/* optional attribute of XSD type xsd:anyType */
	struct soap *soap;	/* transient (not serialized) */
public:
	/// Return the unique type ID value SOAP_TYPE_ns1__Body (21)
	virtual int soap_type(void) const { return 21; }
	/// Set object's data members to default values
	virtual void soap_default(struct soap*);
	/// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
	virtual void soap_serialize(struct soap*) const;
	/// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
	virtual int soap_put(struct soap*, const char *tag, const char *type) const;
	/// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
	virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
	/// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
	virtual void *soap_get(struct soap*, const char *tag, const char *type);
	/// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
	virtual void *soap_in(struct soap*, const char *tag, const char *type);
	/// Return a new object of type ns1__Body, default initialized and not managed by a soap context
	virtual ns1__Body *soap_alloc(void) const { return SOAP_NEW(ns1__Body); }
	         ns1__Body() { ns1__Body::soap_default(NULL); }
	virtual ~ns1__Body() { }
	friend SOAP_FMAC1 ns1__Body * SOAP_FMAC2 soap_instantiate_ns1__Body(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* soap-envelope.h:318 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (28)
/* SOAP-ENV:Detail complex type: */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below)
	   WARNING: do not create a cyclic data structure graph throught this element unless SOAP encoding or SOAP_XML_GRAPH are used for id-ref serialization */
	void *fault;	/* transient (not serialized) */
public:
	int soap_type() const { return 28; } /* = unique type id SOAP_TYPE_SOAP_ENV__Detail */
	         SOAP_ENV__Detail();
	friend SOAP_FMAC1 SOAP_ENV__Detail * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* soap-envelope.h:174 */
#ifndef SOAP_TYPE_ns1__Fault
#define SOAP_TYPE_ns1__Fault (22)
/* ns1:Fault complex type: */
class SOAP_CMAC ns1__Fault
{
public:
	std::string faultcode;	/* required element of XSD type xsd:QName */
	std::string faultstring;	/* required element of XSD type xsd:string */
	std::string *faultactor;	/* optional element of XSD type xsd:anyURI */
	struct SOAP_ENV__Detail *detail;	/* optional element of XSD type SOAP-ENV:Detail */
	struct soap *soap;	/* transient (not serialized) */
public:
	/// Return the unique type ID value SOAP_TYPE_ns1__Fault (22)
	virtual int soap_type(void) const { return 22; }
	/// Set object's data members to default values
	virtual void soap_default(struct soap*);
	/// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
	virtual void soap_serialize(struct soap*) const;
	/// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
	virtual int soap_put(struct soap*, const char *tag, const char *type) const;
	/// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
	virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
	/// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
	virtual void *soap_get(struct soap*, const char *tag, const char *type);
	/// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
	virtual void *soap_in(struct soap*, const char *tag, const char *type);
	/// Return a new object of type ns1__Fault, default initialized and not managed by a soap context
	virtual ns1__Fault *soap_alloc(void) const { return SOAP_NEW(ns1__Fault); }
	         ns1__Fault() { ns1__Fault::soap_default(NULL); }
	virtual ~ns1__Fault() { }
	friend SOAP_FMAC1 ns1__Fault * SOAP_FMAC2 soap_instantiate_ns1__Fault(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* soap-envelope.h:177 */
#ifndef SOAP_TYPE_ns1__detail
#define SOAP_TYPE_ns1__detail (23)
/* ns1:detail complex type: */
class SOAP_CMAC ns1__detail
{
public:
	std::vector<char *> __any;
	char *__anyAttribute;	/* optional attribute of XSD type xsd:anyType */
	struct soap *soap;	/* transient (not serialized) */
public:
	/// Return the unique type ID value SOAP_TYPE_ns1__detail (23)
	virtual int soap_type(void) const { return 23; }
	/// Set object's data members to default values
	virtual void soap_default(struct soap*);
	/// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
	virtual void soap_serialize(struct soap*) const;
	/// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
	virtual int soap_put(struct soap*, const char *tag, const char *type) const;
	/// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
	virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
	/// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
	virtual void *soap_get(struct soap*, const char *tag, const char *type);
	/// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
	virtual void *soap_in(struct soap*, const char *tag, const char *type);
	/// Return a new object of type ns1__detail, default initialized and not managed by a soap context
	virtual ns1__detail *soap_alloc(void) const { return SOAP_NEW(ns1__detail); }
	         ns1__detail() { ns1__detail::soap_default(NULL); }
	virtual ~ns1__detail() { }
	friend SOAP_FMAC1 ns1__detail * SOAP_FMAC2 soap_instantiate_ns1__detail(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* soap-envelope.h:447 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (31)
/* Type SOAP_ENV__Code is a recursive data type (in)directly referencing itself through its (base) class members */
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of XSD type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of XSD type SOAP-ENV:Code */
public:
	int soap_type() const { return 31; } /* = unique type id SOAP_TYPE_SOAP_ENV__Code */
	         SOAP_ENV__Code();
	friend SOAP_FMAC1 SOAP_ENV__Code * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* soap-envelope.h:447 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (35)
/* SOAP-ENV:Reason complex type: */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of XSD type xsd:string */
public:
	int soap_type() const { return 35; } /* = unique type id SOAP_TYPE_SOAP_ENV__Reason */
	         SOAP_ENV__Reason();
	friend SOAP_FMAC1 SOAP_ENV__Reason * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* soap-envelope.h:447 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (36)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of XSD type xsd:QName */
	char *faultstring;	/* optional element of XSD type xsd:string */
	char *faultactor;	/* optional element of XSD type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of XSD type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of XSD type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of XSD type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of XSD type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of XSD type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of XSD type SOAP-ENV:Detail */
public:
	int soap_type() const { return 36; } /* = unique type id SOAP_TYPE_SOAP_ENV__Fault */
	         SOAP_ENV__Fault();
	friend SOAP_FMAC1 SOAP_ENV__Fault * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/


/* soap-envelope.h:101 */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

/* soap-envelope.h:101 */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif

/* soap-envelope.h:145 */
#ifndef SOAP_TYPE_SOAP_ENV__Body
#define SOAP_TYPE_SOAP_ENV__Body (16)
typedef std::string SOAP_ENV__Body;
#endif

/* soap-envelope.h:148 */
#ifndef SOAP_TYPE_SOAP_ENV__encodingStyle
#define SOAP_TYPE_SOAP_ENV__encodingStyle (17)
typedef std::string SOAP_ENV__encodingStyle;
#endif

/* soap-envelope.h:151 */
#ifndef SOAP_TYPE_xsd__anyURI
#define SOAP_TYPE_xsd__anyURI (18)
typedef std::string xsd__anyURI;
#endif

/* soap-envelope.h:192 */
#ifndef SOAP_TYPE_ns1__encodingStyle
#define SOAP_TYPE_ns1__encodingStyle (24)
typedef std::string ns1__encodingStyle;
#endif

/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of soapStub.h */