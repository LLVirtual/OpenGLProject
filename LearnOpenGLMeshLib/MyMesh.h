#ifndef _MY_MESH
#define _MY_MESH

#include "Mesh\Vertex.h"
#include "Mesh\Face.h"
#include "Mesh\Edge.h"
#include "Mesh\HalfEdge.h"
#include "Mesh\BaseMesh.h"
#include "Mesh\boundary.h"
#include "Mesh\iterators.h"
#include "Parser\parser.h"

namespace MeshLib
{
	class CMyVertex;
	class CMyEdge;
	class CMyFace;
	class CMyHalfEdge;
	class CMyVertex : public CVertex
	{
	  public:
		CMyVertex() : m_rgb(1, 1, 1){};
		~CMyVertex() {};

		void _from_string();
		void _to_string();
		CPoint & rgb() { return m_rgb; };
		CPoint2 & uv() { return m_uv; };
	  protected:
		CPoint m_rgb;
		CPoint2 m_uv;
	};
	inline void CMyVertex::_from_string()
	{
		CParser parser(m_string);
		for (std::list<CToken*>::iterator iter = parser.tokens().begin(); iter != parser.tokens().end(); ++iter)
		{
			CToken * token = *iter;
			if (token->m_key == "uv")
			{
				token->m_value >> m_uv;
			}
			if (token->m_key == "rgb")
			{
				token->m_key >> m_rgb;
			}
		}
	};
	inline void CMyVertex::_to_string()
	{
		CParser parser(m_string);
		parser._removeToken("uv");

		parser._toString(m_string);
		std::stringstream iss;

		iss << "uv=(" << m_uv[0] << " " << m_uv[1] << ")";

		if (m_string.length() > 0)
		{
			m_string += " ";
		}
		m_string += iss.str();
	};
	class CMyEdge : public CEdge
	{
	public:
		CMyEdge() :m_sharp(false) {};
		~CMyEdge() {};

		void _from_string();
		void _to_string();

		bool & sharp() { return m_sharp; };
	protected:
		bool m_sharp;
	};

	inline void CMyEdge::_from_string()
	{
		CParser parser(m_string);
		for (std::list<CToken*>::iterator iter = parser.tokens().begin(); iter != parser.tokens().end(); ++iter)
		{
			CToken * token = *iter;
			if (token->m_key == "sharp") // bool
			{
				m_sharp = true;
			}
		}
	}

	inline void CMyEdge::_to_string()
	{
		CParser parser(m_string);
		parser._removeToken("sharp");

		parser._toString(m_string);
		std::stringstream iss;

		if (m_sharp)
			iss << "sharp";

		if (m_string.length() > 0)
		{
			m_string += " ";
		}
		m_string += iss.str();
	}
	class CMyFace : public CFace
	{
	public:

		CPoint & normal() { return m_normal; };
	protected:
		CPoint m_normal;
	};

	class CMyHalfEdge : public CHalfEdge
	{
	};


	template<typename V, typename E, typename F, typename H>
	class MyMesh : public CBaseMesh<V, E, F, H>
	{
	public:
		typedef V V;
		typedef E E;
		typedef F F;
		typedef H H;

		typedef CBoundary<V, E, F, H>					CBoundary;
		typedef CLoop<V, E, F, H>						CLoop;

		typedef MeshVertexIterator<V, E, F, H>			MeshVertexIterator;
		typedef MeshEdgeIterator<V, E, F, H>			MeshEdgeIterator;
		typedef MeshFaceIterator<V, E, F, H>			MeshFaceIterator;
		typedef MeshHalfEdgeIterator<V, E, F, H>		MeshHalfEdgeIterator;

		typedef VertexVertexIterator<V, E, F, H>		VertexVertexIterator;
		typedef VertexEdgeIterator<V, E, F, H>			VertexEdgeIterator;
		typedef VertexFaceIterator<V, E, F, H>			VertexFaceIterator;
		typedef VertexInHalfedgeIterator<V, E, F, H>	VertexInHalfedgeIterator;
		typedef VertexOutHalfedgeIterator<V, E, F, H>	VertexOutHalfedgeIterator;

		typedef FaceVertexIterator<V, E, F, H>			FaceVertexIterator;
		typedef FaceEdgeIterator<V, E, F, H>			FaceEdgeIterator;
		typedef FaceHalfedgeIterator<V, E, F, H>		FaceHalfedgeIterator;
	};

	typedef MyMesh<CMyVertex, CMyEdge, CMyFace, CMyHalfEdge> CMyMesh;
}                                                                                                        
#endif // !_MY_MESH

