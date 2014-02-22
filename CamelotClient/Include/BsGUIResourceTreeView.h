#pragma once

#include "BsEditorPrerequisites.h"
#include "BsGUITreeView.h"
#include "BsVirtualInput.h"
#include "CmPath.h"
#include <boost/signal.hpp>

namespace BansheeEditor
{
	class GUIResourceTreeView : public GUITreeView
	{
		struct ResourceTreeElement : public GUITreeView::TreeElement
		{
			CM::WPath mFullPath;
		};

		struct DraggedResources
		{
			CM::Vector<CM::String>::type resourceUUIDs;
		};

		struct InternalDraggedResources
		{
			InternalDraggedResources(CM::UINT32 numObjects);
			~InternalDraggedResources();

			CM::UINT32 numObjects;
			CM::WPath* resourcePaths;
		};

	public:
		static const CM::String& getGUITypeName();

		static GUIResourceTreeView* create(BS::GUIWidget& parent,
			BS::GUIElementStyle* backgroundStyle = nullptr, BS::GUIElementStyle* elementBtnStyle = nullptr, 
			BS::GUIElementStyle* foldoutBtnStyle = nullptr, BS::GUIElementStyle* selectionBackgroundStyle = nullptr,
			BS::GUIElementStyle* editBoxStyle = nullptr, BS::GUIElementStyle* dragHighlightStyle = nullptr, 
			BS::GUIElementStyle* dragSepHighlightStyle = nullptr);

		static GUIResourceTreeView* create(BS::GUIWidget& parent, const BS::GUIOptions& options, 
			BS::GUIElementStyle* backgroundStyle = nullptr, BS::GUIElementStyle* elementBtnStyle = nullptr, 
			BS::GUIElementStyle* foldoutBtnStyle = nullptr, BS::GUIElementStyle* selectionBackgroundStyle = nullptr,
			BS::GUIElementStyle* editBoxStyle = nullptr, BS::GUIElementStyle* dragHighlightStyle = nullptr, 
			BS::GUIElementStyle* dragSepHighlightStyle = nullptr);


	protected:
		virtual ~GUIResourceTreeView();

	protected:
		InternalDraggedResources* mDraggedResources;
		ResourceTreeElement mRootElement;
		CM::RenderWindow* mCurrentWindow;
		CM::OSDropTarget* mDropTarget;
		bool mDropTargetDragActive;

		boost::signals::connection mDropTargetEnterConn;
		boost::signals::connection mDropTargetMoveConn;
		boost::signals::connection mDropTargetLeaveConn;
		boost::signals::connection mDropTargetDroppedConn;

		GUIResourceTreeView(BS::GUIWidget& parent, BS::GUIElementStyle* backgroundStyle, BS::GUIElementStyle* elementBtnStyle, 
			BS::GUIElementStyle* foldoutBtnStyle, BS::GUIElementStyle* selectionBackgroundStyle, BS::GUIElementStyle* editBoxStyle, 
			BS::GUIElementStyle* dragHighlightStyle, BS::GUIElementStyle* dragSepHighlightStyle, const BS::GUILayoutOptions& layoutOptions);

		virtual void _updateLayoutInternal(CM::INT32 x, CM::INT32 y, CM::UINT32 width, CM::UINT32 height,
			CM::RectI clipRect, CM::UINT8 widgetDepth, CM::UINT16 areaDepth);

		virtual TreeElement& getRootElement() { return mRootElement; }
		virtual const TreeElement& getRootElementConst() const { return mRootElement; }
		virtual void updateTreeElementHierarchy();
		virtual void renameTreeElement(TreeElement* element, const CM::WString& name);
		virtual bool acceptDragAndDrop() const;
		virtual void dragAndDropStart();
		virtual void dragAndDropEnded(TreeElement* overTreeElement);
		virtual void dragAndDropFinalize();

		ResourceTreeElement* addTreeElement(ResourceTreeElement* parent, const CM::WPath& fullPath);
		void deleteTreeElement(ResourceTreeElement* element);
		void sortTreeElement(ResourceTreeElement* element);

		ResourceTreeElement* findTreeElement(const CM::WPath& fullPath);

		void entryAdded(const CM::WPath& path);
		void entryRemoved(const CM::WPath& path);

		void setDropTarget(CM::RenderWindow* parentWindow, CM::INT32 x, CM::INT32 y, CM::UINT32 width, CM::UINT32 height);
		void clearDropTarget();

		void dropTargetDragMove(CM::INT32 x, CM::INT32 y);
		void dropTargetDragLeave();
		void dropTargetDragDropped(CM::INT32 x, CM::INT32 y);

		void quicksortTreeElements(CM::Vector<TreeElement*>::type& elements, CM::INT32 first, CM::INT32 last);

		CM::WPath findUniquePath(const CM::WPath& path);

		void _changeParentWidget(BS::GUIWidget* widget);
	};
}