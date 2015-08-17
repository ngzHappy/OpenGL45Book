#ifndef __TEMPLATE__STRING__HPP__0x00
#define __TEMPLATE__STRING__HPP__0x00

/** . ? + $ ^ [ ] ( ) { } | \ / */
#include <regex>
#include <memory>
#ifdef QT_CORE_LIB
#include <QString>
#include <QRegExp>
#endif

/*
lick python string.Template
substitute
${} must be added!!
*/

namespace gl {


template<typename StringType>
class TemplateString {
public:
    typedef StringType string_type;
    class Data {
    public:
        StringType source;
        Data(const StringType & v):source(v) {}
        Data( StringType && v) :source(std::move(v)){}
    };
    std::shared_ptr<Data> data;

    TemplateString(const StringType & v):
        data(std::shared_ptr<Data>( new Data(v))){
    }
    TemplateString(StringType && v) :
        data(std::shared_ptr<Data>(new Data( std::move(v) ))) {
    }

    StringType operator()(
        const StringType & before_0,
        const StringType & after_0
        ) const{
        StringType ans;

        const auto & source = data->source;
        ans.reserve( source.size()+64 );
        typedef decltype(source.cbegin()) _i_type;
        typedef typename StringType::value_type _value_type;

        constexpr static  const _value_type _0b[] = {'\\', '$','\\','{','\0',0 };
        constexpr static  const _value_type _0e[] = {'\\', '}','\0',0  };

        std::match_results<_i_type> m;
        std::basic_regex<_value_type> e(
            StringType(_0b) +
            before_0 +
            StringType(_0e)
            );

        auto source_begin = source.cbegin();
        auto source_end = source.cend();

        while (std::regex_search(source_begin, source_end, m, e)) {
            auto & subs = *(m.begin());
            ans += StringType(source_begin, subs.first);
            ans += after_0;
            source_begin = subs.second;
        }

        ans += StringType(source_begin, source_end);

        return std::move(ans);

    }

    template<typename T1, typename T2,typename T3 ,typename ... Args>
    StringType operator()(
        const T1 & before_,
        const T2 & after_,
        const T3 & next_begin_,
        const Args & ... args
        ) {
        StringType _temp = this->operator()(before_, after_);
        TemplateString _temp_string( std::move(_temp) );
        return std::move( _temp_string(next_begin_,args...) );
    }

	template<typename ... Args>
	StringType substitute(const Args& ...args ) {
		return this->operator()(args...);
	}

};

#ifdef QT_CORE_LIB
template<>
class TemplateString<QString> {
public:
    typedef QString StringType;
    typedef QString string_type;

    class Data {
    public:
        StringType source;
        Data(const StringType & v) :source(v) {}
        Data(StringType && v) :source(std::move(v)) {}
    };
    std::shared_ptr<Data> data;

    TemplateString(const StringType & v) :
        data(std::shared_ptr<Data>(new Data(v))) {
    }
    TemplateString(StringType && v) :
        data(std::shared_ptr<Data>(new Data(std::move(v)))) {
    }

    QString operator()(
        const QString & before_0,
        const QString & after_0
        ) const {
        QString ans;
        const QString & source = data->source;
        auto __ss = source.size();
        ans.reserve(__ss+64);
        QRegExp e(StringType("\\$\\{") + before_0 + StringType("\\}"),
            Qt::CaseSensitive,
            QRegExp::RegExp2);
        int pos = 0;
        int pos_start = 0;
        while ((pos = e.indexIn(source, pos)) != -1) {
            ans += source.midRef(pos_start,pos-pos_start);
            ans += after_0;
            pos += e.matchedLength();
            pos_start = pos;
        }
        ans += source.midRef(pos_start, __ss);
        return std::move(ans);
    }

    template<typename T1, typename T2, typename T3, typename ... Args>
    StringType operator()(
        const T1 & before_,
        const T2 & after_,
        const T3 & next_begin_,
        const Args & ... args
        ) {
        StringType _temp = this->operator()(before_, after_);
        TemplateString _temp_string(std::move(_temp));
        return std::move( _temp_string(next_begin_, args...) );
    }

	template<typename ... Args>
	StringType substitute(const Args& ...args) {
		return this->operator()(args...);
	}

};
#endif

}//~namesapce gl

#endif
