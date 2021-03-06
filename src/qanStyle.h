/*
    This file is part of QuickQanava library.

    Copyright (C) 2008-2017 Benoit AUTHEMAN

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library.
//
// \file    qanStyle.h
// \author  benoit@destrat.io
// \date    2015 06 05
//-----------------------------------------------------------------------------

#ifndef qanStyle_h
#define qanStyle_h

// QuickContainers headers
#include "../QuickContainers/src/qcmObjectModel.h"

// Qt headers
#include <QColor>
#include <QFont>
#include <QSizeF>

namespace qan { // ::qan

/*! Models a set of properties affecting a graph primitive visual appearance.
 *
 *  Style instances should be created from StyleManager createStyle() or createStyleFrom() methods,
 *  and associed to nodes trought their setStyle() method. Changing a style property will
 *  automatically be reflected in styled nodes or edges appearance. While Style use standard QObject
 *  properties to store style settings, the QuickContainers ObjectModel interface could be use to edit
 *  style properties.
 *
 *  Main qan::Style properties are:
 * \li \b name: Style name as it will appears in style edition dialogs.
 *
 * \sa qan::NodeItem::setStyle()
 * \sa qan::EdgeItem::setStyle()
 */
class Style : public QObject
{
    Q_OBJECT
    /*! \name Style Object Management *///-------------------------------------
    //@{
public:
    /*! \brief Style constructor with style name initialisation.
     */
    explicit Style( QString name = "", QObject* parent = nullptr );
    virtual ~Style( ) { }
    Style( const Style& ) = delete;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Style Management *///--------------------------------------------
    //@{
public:
    Q_PROPERTY( QString name READ getName WRITE setName NOTIFY nameChanged FINAL )
    inline  void        setName( QString name ) noexcept { if ( name != _name ) { _name = name; emit nameChanged( ); } }
    inline  QString     getName() noexcept { return _name; }
    inline  QString     getName() const noexcept { return _name; }
signals:
    void        nameChanged( );
private:
    QString     _name{ QStringLiteral("") };

public:
    /*! \brief Generate a deep copy of this Style object, ownsership return to the caller.
     *
     * Static properties of this source object may be converted in dynamic properties in
     * destination object as their is no way to dynamically generate static properties with
     * QObject outside QML.
     *
     * Existing properties (either static or dynamic) in duplicated object will be set to
     * this style value (for exemple objectName, target, etc.).
     *
     * \note 20150630: deep copy of time values is currently not supported.
     * \param   dstParent optionnal parent for the duplicated style object.
     */
    qan::Style*     duplicate( QString duplicatedStyleName, QObject* dstParent = nullptr );
    //@}
    //-------------------------------------------------------------------------
};

class NodeStyle : public qan::Style
{
    /*! \name NodeStyle Object Management *///---------------------------------
    //@{
    Q_OBJECT
public:
    /*! \brief Style constructor with style \c name and \c target initialisation.
     *
     * Style \c metaTarget is "qan::Node". NodeStyle objects are usually created
     * with qan:StyleManager::createNodeStyle() factory method.
     */
    explicit NodeStyle( QString name = "", QObject* parent = nullptr );
    virtual ~NodeStyle( ) { }
    NodeStyle( const NodeStyle& ) = delete;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Properties Management *///---------------------------------------
    //@{
public:
    Q_PROPERTY( QColor backColor READ getBackColor WRITE setBackColor NOTIFY backColorChanged FINAL )
    void            setBackColor( const QColor& backColor ) noexcept { _backColor = backColor; emit backColorChanged( ); }
    const QColor&   getBackColor() const noexcept { return _backColor; }
protected:
    QColor          _backColor{Qt::white};
signals:
    void            backColorChanged();

public:
    Q_PROPERTY( QColor borderColor READ getBorderColor WRITE setBorderColor NOTIFY borderColorChanged FINAL )
    void            setBorderColor( const QColor& borderColor ) noexcept { _borderColor = borderColor; emit borderColorChanged( ); }
    const QColor&   getBorderColor() const noexcept { return _borderColor; }
protected:
    QColor          _borderColor = QColor( Qt::black );
signals:
    void            borderColorChanged();

public:
    Q_PROPERTY( qreal borderWidth READ getBorderWidth WRITE setBorderWidth NOTIFY borderWidthChanged FINAL )
    void            setBorderWidth( qreal borderWidth ) noexcept { _borderWidth = borderWidth; emit borderWidthChanged( ); }
    inline qreal    getBorderWidth() const noexcept { return _borderWidth; }
protected:
    qreal           _borderWidth = 1.0;
signals:
    void            borderWidthChanged();

public:
    Q_PROPERTY( bool hasShadow READ getHasShadow WRITE setHasShadow NOTIFY hasShadowChanged FINAL )
    void            setHasShadow( bool hasShadow ) noexcept { _hasShadow = hasShadow; emit hasShadowChanged( ); }
    inline bool     getHasShadow() const noexcept { return _hasShadow; }
protected:
    bool            _hasShadow = true;
signals:
    void            hasShadowChanged();

public:
    Q_PROPERTY( QColor shadowColor READ getShadowColor WRITE setShadowColor NOTIFY shadowColorChanged FINAL )
    void            setShadowColor( QColor shadowColor ) noexcept { _shadowColor = shadowColor; emit shadowColorChanged( ); }
    inline QColor   getShadowColor() const noexcept { return _shadowColor; }
protected:
    QColor          _shadowColor = QColor{ 0, 0, 0, 127 };
signals:
    void            shadowColorChanged();

public:
    Q_PROPERTY( qreal shadowRadius READ getShadowRadius WRITE setShadowRadius NOTIFY shadowRadiusChanged FINAL )
    void            setShadowRadius( qreal shadowRadius ) noexcept { _shadowRadius = shadowRadius; emit shadowRadiusChanged( ); }
    inline qreal    getShadowRadius() const noexcept { return _shadowRadius; }
protected:
    qreal           _shadowRadius{3.};
signals:
    void            shadowRadiusChanged();
    //@}
    //-------------------------------------------------------------------------
};

class EdgeStyle : public qan::Style
{
    Q_OBJECT
    /*! \name EdgeStyle Object Management *///---------------------------------
    //@{
public:
    /*! \brief Edge style constructor with style \c name and \c target initialisation.
     *
     */
    explicit EdgeStyle( QString name = "", QObject* parent = nullptr );
    virtual ~EdgeStyle( ) { }
    EdgeStyle( const EdgeStyle& ) = delete;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Properties Management *///---------------------------------------
    //@{
signals:
    void            styleModified();

public:
    Q_PROPERTY( QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged FINAL )
    void            setLineColor( const QColor& lineColor ) noexcept { _lineColor = lineColor; emit lineColorChanged( ); emit styleModified(); }
    const QColor&   getLineColor() const noexcept { return _lineColor; }
protected:
    QColor          _lineColor = QColor( 0, 0, 0, 255 );
signals:
    void            lineColorChanged();

public:
    Q_PROPERTY( qreal lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged FINAL )
    void            setLineWidth( qreal lineWidth ) noexcept { _lineWidth = lineWidth; emit lineWidthChanged( ); emit styleModified();  }
    qreal           getLineWidth() const noexcept { return _lineWidth; }
protected:
    qreal           _lineWidth = 2.0;
signals:
    void            lineWidthChanged();

public:
    Q_PROPERTY( qreal arrowSize READ getArrowSize WRITE setArrowSize NOTIFY arrowSizeChanged FINAL )
    void            setArrowSize( qreal arrowSize ) noexcept { _arrowSize = arrowSize; emit arrowSizeChanged( ); emit styleModified();  }
    qreal           getArrowSize() const noexcept { return _arrowSize; }
protected:
    qreal           _arrowSize = 4.0;
signals:
    void            arrowSizeChanged();
    //@}
    //-------------------------------------------------------------------------
};

} // ::qan

QML_DECLARE_TYPE( qan::Style )
QML_DECLARE_TYPE( qan::NodeStyle )
QML_DECLARE_TYPE( qan::EdgeStyle )

#endif // qanStyle_h

